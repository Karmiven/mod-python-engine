#include "PythonEngine.h"
#include "ScriptMgr.h"

// Forward declarations
void AddPythonAccountScripts();
void AddPythonCommandScripts();
void AddPythonCreatureScripts();
void AddPythonGameObjectScripts();
void AddPythonPlayerScripts();

class PythonLoader : public WorldScript
{
public:
    PythonLoader() : WorldScript("PythonLoader") {}

    void OnStartup() override
    {
        // Initialize the Engine (creates the Python VM, registers bindings) and
        // immediately load all scripts from ScriptsPath
        // @todo Check if OnBeforeConfigLoad is better to init engine
        sPythonEngine->Initialize();
        sPythonEngine->LoadScripts();
    }

    void OnShutdown() override
    {
        // Ensure the Python engine is turned off safely, preventing memory
        // leaks or hanging processes
        // @todo Check if OnAfterUnloadAllMaps is better to shutdown engine
        sPythonEngine->Shutdown();
    }
};

void Addmod_python_engineScripts()
{
    new PythonLoader();

    AddPythonAccountScripts();
    AddPythonCommandScripts();
    AddPythonCreatureScripts();
    AddPythonGameObjectScripts();
    AddPythonPlayerScripts();
}
