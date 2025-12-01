#ifndef MOD_PYTHON_ENGINE_HOOKS_H
#define MOD_PYTHON_ENGINE_HOOKS_H

#include "Define.h"
#include <optional>
#include <string>
#include <unordered_map>

enum class PythonHook : uint32
{
    UNKNOWN = 0,

    // Account
    ACCOUNT_FAILED_LOGIN,
    ACCOUNT_LOGIN,

    // Creature
    CREATURE_ADD_WORLD,
    CREATURE_GOSSIP_HELLO,
    CREATURE_GOSSIP_SELECT,
    CREATURE_REMOVE_WORLD,

    // GameObject
    GAMEOBJECT_ADD_WORLD,
    GAMEOBJECT_GOSSIP_HELLO,
    GAMEOBJECT_GOSSIP_SELECT,
    GAMEOBJECT_REMOVE_WORLD,

    // Player
    PLAYER_DUEL_END,
    PLAYER_DUEL_REQUEST,
    PLAYER_DUEL_START,
    PLAYER_GIVE_XP,
    PLAYER_JUST_DIED,
    PLAYER_LEVEL_CHANGED,
    PLAYER_LOGIN,
    PLAYER_LOGOUT,
    PLAYER_MONEY_CHANGED,
    PLAYER_PVP_KILL,

    // ...
};

// Resolves a string event name to its corresponding PythonHook enum value.
// Get name of the event (for ex., "PLAYER_LOGIN") and return Hook ID if found,
// otherwise std::nullopt.
inline std::optional<PythonHook> GetPythonHookByName(const std::string& name)
{
    static const std::unordered_map<std::string, PythonHook> eventRegistry = {
        // Account
        { "ACCOUNT_FAILED_LOGIN",    PythonHook::ACCOUNT_FAILED_LOGIN    },
        { "ACCOUNT_LOGIN",           PythonHook::ACCOUNT_LOGIN           },

        // Creature
        { "CREATURE_ADD_WORLD",      PythonHook::CREATURE_ADD_WORLD      },
        { "CREATURE_GOSSIP_HELLO",   PythonHook::CREATURE_GOSSIP_HELLO   },
        { "CREATURE_GOSSIP_SELECT",  PythonHook::CREATURE_GOSSIP_SELECT  },
        { "CREATURE_REMOVE_WORLD",   PythonHook::CREATURE_REMOVE_WORLD   },

        // GameObject
        { "GAMEOBJECT_ADD_WORLD",    PythonHook::GAMEOBJECT_ADD_WORLD    },
        { "GAMEOBJECT_GOSSIP_HELLO", PythonHook::GAMEOBJECT_GOSSIP_HELLO },
        { "CREATURE_GOSSIP_SELECT",  PythonHook::CREATURE_GOSSIP_SELECT  },
        { "CREATURE_REMOVE_WORLD",   PythonHook::CREATURE_REMOVE_WORLD   },

        // Player
        { "PLAYER_DUEL_END",         PythonHook::PLAYER_DUEL_END         },
        { "PLAYER_DUEL_REQUEST",     PythonHook::PLAYER_DUEL_REQUEST     },
        { "PLAYER_DUEL_START",       PythonHook::PLAYER_DUEL_START       },
        { "PLAYER_GIVE_XP",          PythonHook::PLAYER_GIVE_XP          },
        { "PLAYER_JUST_DIED",        PythonHook::PLAYER_JUST_DIED        },
        { "PLAYER_LEVEL_CHANGED",    PythonHook::PLAYER_LEVEL_CHANGED    },
        { "PLAYER_LOGIN",            PythonHook::PLAYER_LOGIN            },
        { "PLAYER_LOGOUT",           PythonHook::PLAYER_LOGOUT           },
        { "PLAYER_MONEY_CHANGED",    PythonHook::PLAYER_MONEY_CHANGED    },
        { "PLAYER_PVP_KILL",         PythonHook::PLAYER_PVP_KILL         },

        // ...
    };

    auto it = eventRegistry.find(name);
    if (it != eventRegistry.end())
        return it->second;

    return std::nullopt;
}

#endif // MOD_PYTHON_ENGINE_HOOKS_H
