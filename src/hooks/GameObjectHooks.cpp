#include "PythonEngine.h"
#include "ScriptMgr.h"
#include "GameObject.h"
#include "Player.h"

class PythonGameObjectScript : public AllGameObjectScript
{
public:
    PythonGameObjectScript() : AllGameObjectScript("PythonGameObjectScript") {}

    void OnGameObjectAddWorld(GameObject* go) override
    {
        sPythonEngine->Trigger(PythonHook::GAMEOBJECT_ADD_WORLD, go->GetEntry(), go);
    }

    void OnGameObjectRemoveWorld(GameObject* go) override
    {
        sPythonEngine->Trigger(PythonHook::CREATURE_REMOVE_WORLD, go->GetEntry(), go);
    }

    bool CanGameObjectGossipHello(Player* player, GameObject* go) override
    {
        sPythonEngine->Trigger(PythonHook::GAMEOBJECT_GOSSIP_HELLO, go->GetEntry(), player, go);
        return false;
    }

    bool CanGameObjectGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) override
    {
        sPythonEngine->Trigger(PythonHook::GAMEOBJECT_GOSSIP_SELECT, go->GetEntry(), player, go, sender, action);
        return false;
    }
};

void AddPythonGameObjectScripts()
{
    new PythonGameObjectScript();
}
