#ifndef MOD_PYTHON_ENGINE_PLAYER_METHODS_H
#define MOD_PYTHON_ENGINE_PLAYER_METHODS_H

#include "Player.h"
#include "Chat.h"

namespace PythonPlayerMethods
{
    inline void AddItem(Player* player, uint32 itemId, uint32 count)
    {
        if (player)
            player->AddItem(itemId, count);
    }

    inline void Say(Player* player, const std::string& text, uint32 language)
    {
        if (player)
            player->Say(text, static_cast<Language>(language));
    }

    inline void SendSysMessage(Player* player, const std::string& text)
    {
        if (player && player->GetSession())
        {
            ChatHandler handler(player->GetSession());
            handler.SendSysMessage(text);
        }
    }

    inline uint32 GetGUIDLow(Player* player)
    {
        return player ? player->GetGUID().GetCounter() : 0;
    }
}

#endif // MOD_PYTHON_ENGINE_PLAYER_METHODS_H
