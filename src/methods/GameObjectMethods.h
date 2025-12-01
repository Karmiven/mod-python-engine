#ifndef MOD_PYTHON_ENGINE_GAMEOBJECT_METHODS_H
#define MOD_PYTHON_ENGINE_GAMEOBJECT_METHODS_H

#include "GameObject.h"

namespace PythonGameObjectMethods
{
    inline void Respawn(GameObject* go)
    {
        if (go)
            go->Respawn();
    }

    inline void Use(GameObject* go, Unit* unit)
    {
        if (go)
            go->Use(unit);
    }

    inline uint32 GetGUIDLow(GameObject* go)
    {
        return go ? go->GetGUID().GetCounter() : 0;
    }
}

#endif // MOD_PYTHON_ENGINE_GAMEOBJECT_METHODS_H
