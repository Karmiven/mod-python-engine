#ifndef MOD_PYTHON_ENGINE_H
#define MOD_PYTHON_ENGINE_H

#include "PythonAPI.h"
#include "PythonConverter.h"
#include "PythonGIL.h"
#include "HookInfo.h"
#include "Define.h"
#include <atomic>
#include <shared_mutex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// Forward declaration
void InitAzerothCoreModule();

using namespace PyEng::Bridge;
using HookInfo = PyEng::Hooks::HookInfo;

class PythonEngine
{
public:
    [[nodiscard]] static PythonEngine* instance();

    PythonEngine(const PythonEngine&) = delete;
    PythonEngine& operator=(const PythonEngine&) = delete;

    void Initialize();
    void LoadScripts();
    void ReloadScripts();
    void Shutdown();

    /**
     * @brief Register a Python callback for a game event hook
     *
     * @param eventName Hook event name (ex., "PLAYER_ON_LOGIN")
     * @param callback Python callable object
     * @param entryId Specific entry ID (creature, item, etc.; 0 for global)
     */
    void RegisterHook(const std::string& eventName, API::Object callback, uint32 entryId = 0);

    [[nodiscard]] bool IsEnabled() const { return enabled; }

    /**
     * @brief Main bridge between C++ game logic and Python scripts
     *
     * When a specific game event occurs (ex., player login, creature death),
     * this method looks up all registered Python callbacks and executes them.
     *
     * @param hinfo Hook identifier to trigger
     * @param entryId Specific entry ID (creature, item, etc.; 0 for global)
     * @param args Variadic arguments to pass to Python callbacks
     */
    template<typename... Args>
    void Trigger(HookInfo hinfo, uint32 entryId, Args&&... args)
    {
        if (!enabled || reloading || !HasBindingsFor(hinfo, entryId))
            return;

        auto argsTuple = std::make_tuple(std::forward<Args>(args)...);
        std::shared_lock<std::shared_mutex> lock(hookMutex);

        // CRITICAL: Double-check reloading after acquiring lock. Prevent race
        // conditions with reload scripts operations.
        if (reloading)
            return;

        TriggerDepthGuard depthGuard;

        auto itr = hookMap.find(hinfo);
        if (itr == hookMap.end())
            return;

        TriggerCallbacks(itr->second, 0, argsTuple); // global hooks
        if (entryId > 0)
            TriggerCallbacks(itr->second, entryId, argsTuple); // entry-specific hooks
    }

    static void TriggerHook(HookInfo* hinfo, uint32 entryId);

private:
    using CallbackList = std::vector<API::Object>;
    using HookEntryMap = std::unordered_map<uint32, CallbackList>;
    using HookRegistry = std::unordered_map<HookInfo, HookEntryMap>;

    PythonEngine() = default;
    ~PythonEngine();

    void ExecuteScript(const std::string& filepath);
    void LogException();

    // RAII guard for tracking Trigger depth
    struct TriggerDepthGuard
    {
        TriggerDepthGuard() { PythonEngine::triggerDepth++; }
        ~TriggerDepthGuard() { PythonEngine::triggerDepth--; }
        TriggerDepthGuard(const TriggerDepthGuard&) = delete;
        TriggerDepthGuard& operator=(const TriggerDepthGuard&) = delete;
    };

    /**
     * @brief Check if any callbacks are registered for a specific hook
     *
     * @param hinfo Hook identifier to check
     * @param entryId Specific entry ID (creature, item, etc.; 0 for global)
     * @return True if callbacks registered, false otherwise
     */
    [[nodiscard]] bool HasBindingsFor(HookInfo hinfo, uint32 entryId = 0) const noexcept
    {
        auto itr = hookMap.find(hinfo);
        if (itr == hookMap.end())
            return false;

        auto callbacks = [&](uint32 id)
        {
            auto it = itr->second.find(id);
            return it != itr->second.end() && !it->second.empty();
        };

        return callbacks(0) || (entryId > 0 && callbacks(entryId));
    }

    /**
     * @brief Executes all registered Python callbacks for a specific hook
     *
     * @param entryMap Map of entity IDs to callback vectors
     * @param entryId Specific entry ID (creature, item, etc.; 0 for global)
     * @param argsTuple Tuple of C++ arguments to pass to Python callbacks
     */
    template<typename Tuple>
    void TriggerCallbacks(const HookEntryMap& entryMap, uint32 entryId, const Tuple& argsTuple)
    {
        auto itr = entryMap.find(entryId);
        if (itr == entryMap.end())
            return;

        GILGuard gil;

        for (const auto& callback : itr->second)
        {
            try
            {
                std::apply([&](const auto&... unpacked_args) {
                    callback(Converter::ToPython(unpacked_args)...);
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

    HookRegistry hookMap;
    API::Object main_namespace;
};

extern PythonEngine* sPythonEngine;

#define sPythonEngine PythonEngine::instance()

#endif // MOD_PYTHON_ENGINE_H
