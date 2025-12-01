#include "PythonEngine.h"
#include "ScriptMgr.h"

class PythonAccountScript : public AccountScript
{
public:
    PythonAccountScript() : AccountScript("PythonAccountScript") {}

    void OnAccountLogin(uint32 accountId) override
    {
        sPythonEngine->Trigger(PythonHook::ACCOUNT_LOGIN, 0, accountId);
    }

    void OnFailedAccountLogin(uint32 accountId) override
    {
        sPythonEngine->Trigger(PythonHook::ACCOUNT_FAILED_LOGIN, 0, accountId);
    }
};

void AddPythonAccountScripts()
{
    new PythonAccountScript();
}
