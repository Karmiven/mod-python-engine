#ifndef MOD_PYTHON_ENGINE_UNIT_METHODS_H
#define MOD_PYTHON_ENGINE_UNIT_METHODS_H

#include "Unit.h"

namespace PythonUnitMethods
{
    inline uint32 GetGUIDLow(Unit* unit)
    {
        return unit ? unit->GetGUID().GetCounter() : 0;
    }
}

#endif // MOD_PYTHON_ENGINE_UNIT_METHODS_H
