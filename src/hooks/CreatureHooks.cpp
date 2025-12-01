#include "PythonEngine.h"
#include "ScriptMgr.h"
#include "Creature.h"
#include "Player.h"

class PythonCreatureScript : public AllCreatureScript
{
public:
    PythonCreatureScript() : AllCreatureScript("PythonCreatureScript") {}

    void OnCreatureAddWorld(Creature* creature) override
    {
        sPythonEngine->Trigger(PythonHook::CREATURE_ADD_WORLD, creature->GetEntry(), creature);
    }

    void OnCreatureRemoveWorld(Creature* creature) override
    {
        sPythonEngine->Trigger(PythonHook::CREATURE_REMOVE_WORLD, creature->GetEntry(), creature);
    }

    bool CanCreatureGossipHello(Player* player, Creature* creature) override
    {
        sPythonEngine->Trigger(PythonHook::CREATURE_GOSSIP_HELLO, creature->GetEntry(), player, creature);
        return false;
    }

    bool CanCreatureGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        sPythonEngine->Trigger(PythonHook::CREATURE_GOSSIP_SELECT, creature->GetEntry(), player, creature, sender,
                               action);
        return false;
    }
};

void AddPythonCreatureScripts()
{
    new PythonCreatureScript();
}
