#ifndef MOD_PYTHON_ENGINE_CREATURE_METHODS_H
#define MOD_PYTHON_ENGINE_CREATURE_METHODS_H

#include "Creature.h"

namespace PythonCreatureMethods
{
    inline void Respawn(Creature* creature)
    {
        if (creature)
            creature->Respawn();
    }

    inline void SetHomePosition(Creature* creature, float x, float y, float z, float o)
    {
        if (creature)
            creature->SetHomePosition(x, y, z, o);
    }

    inline uint32 GetGUIDLow(Creature* creature)
    {
        return creature ? creature->GetGUID().GetCounter() : 0;
    }
}

#endif // MOD_PYTHON_ENGINE_CREATURE_METHODS_H
