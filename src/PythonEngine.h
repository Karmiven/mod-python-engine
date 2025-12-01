#ifndef MOD_PYTHON_ENGINE_ENGINE_H
#define MOD_PYTHON_ENGINE_ENGINE_H

#include "PythonAPI.h"
#include "PythonHooks.h"
#include "Define.h"
#include <atomic>
#include <shared_mutex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// Forward declaration
void InitAzerothCoreModule();

class PythonEngine
{
public:
    [[nodiscard]] static PythonEngine* instance();
    PythonEngine(const PythonEngine&) = delete;
    PythonEngine& operator=(const PythonEngine&) = delete;

    // Core API
    void Initialize();
    void LoadScripts();
    void ReloadScripts();
    void Shutdown();
    void RegisterHook(const std::string& eventName, PythonAPI::Object callback, uint32 entryId = 0);

    [[nodiscard]] bool IsEnabled() const { return enabled; }

    // Main bridge between C++ game logic and Python scripts. When a specific
    // game event occurs (e.g., player login, creature death), this method
    // looks up all registered Python callbacks and executes them.
    template<typename... Args>
    void Trigger(PythonHook hookId, uint32 entryId, Args&&... args)
    {
        if (!enabled || reloading)
            return;

        auto argsTuple = std::make_tuple(std::forward<Args>(args)...);

        std::shared_lock<std::shared_mutex> lock(hookMutex);
        TriggerDepthGuard depthGuard;

        auto hook = hookRegistry.find(hookId);
        if (hook == hookRegistry.end())
            return;

        TriggerCallbacks(hook->second, 0, argsTuple); // global hooks
        if (entryId > 0)
            TriggerCallbacks(hook->second, entryId, argsTuple); // specific hooks
    }

private:
    PythonEngine() = default;
    ~PythonEngine();

    void ExecuteScript(const std::string& filepath);
    void LogException();
    void LogPythonError();

    // RAII guard for Trigger Depth
    struct TriggerDepthGuard
    {
        TriggerDepthGuard() { PythonEngine::triggerDepth++; }
        ~TriggerDepthGuard() { PythonEngine::triggerDepth--; }
        TriggerDepthGuard(const TriggerDepthGuard&) = delete;
        TriggerDepthGuard& operator=(const TriggerDepthGuard&) = delete;
    };

    // Type converters
    template<typename T> static PythonAPI::Object to_py(T&& v) { return PythonAPI::Object(std::forward<T>(v)); }
    template<typename T> static PythonAPI::Object to_py(T* p) { if (!p) return PythonAPI::Object(); return PythonAPI::Object(PythonAPI::Ptr(p)); }
    static PythonAPI::Object to_py(const char* s) { return PythonAPI::FromString(std::string(s)); }
    static PythonAPI::Object to_py(const std::string& s) { return PythonAPI::FromString(s); }

    // Performs the actual execution of Python functions registered for a given
    // event and entity combination
    template<typename Tuple>
    void TriggerCallbacks(const std::unordered_map<uint32, std::vector<PythonAPI::Object>>& entry, uint32 entryId,
                          const Tuple& argsTuple)
    {
        auto it = entry.find(entryId);
        if (it == entry.end())
            return;

        PythonAPI::GILGuard gil;
        for (const auto& callback : it->second)
        {
            try
            {
                std::apply([&](const auto&... unpacked_args) {
                    callback(to_py(unpacked_args)...);
                }, argsTuple);
            }
            catch (...)
            {
                LogException();
            }
        }
    }

    std::atomic<bool> enabled{false};
    std::atomic<bool> reloading{false};
    mutable std::shared_mutex hookMutex;

    inline static thread_local int triggerDepth = 0;

    std::unordered_map<PythonHook, std::unordered_map<uint32, std::vector<PythonAPI::Object>>> hookRegistry;
    PythonAPI::Object main_namespace;
};

#define sPythonEngine PythonEngine::instance()

#endif // MOD_PYTHON_ENGINE_ENGINE_H
