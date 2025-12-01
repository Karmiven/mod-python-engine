#include "PythonEngine.h"
#include "ScriptMgr.h"
#include "Player.h"

class PythonPlayerScript : public PlayerScript
{
public:
    PythonPlayerScript() : PlayerScript("PythonPlayerScript") {}

    void OnPlayerLogin(Player* player) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_LOGIN, 0, player);
    }

    void OnPlayerLogout(Player* player) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_LOGOUT, 0, player);
    }

    void OnPlayerPVPKill(Player* killer, Player* killed) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_PVP_KILL, 0, killer, killed);
    }

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_GIVE_XP, 0, player, amount, victim, xpSource);
    }

    void OnPlayerLevelChanged(Player* player, uint8 oldLevel) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_LEVEL_CHANGED, 0, player, oldLevel);
    }

    void OnPlayerMoneyChanged(Player* player, int32& amount) override
    {
        sPythonEngine->Trigger(PythonHook::PLAYER_MONEY_CHANGED, 0, player, amount);
    }
};

void AddPythonPlayerScripts()
{
    new PythonPlayerScript();
}
