#include "PythonEngine.h"
#include "CreatureMethods.h"
#include "GameObjectMethods.h"
#include "PlayerMethods.h"
#include "UnitMethods.h"
#include <stdexcept>

namespace bp = boost::python;

// Forward declaration of the constants export function
void export_constants();

extern "C" PyObject* PyInit_azerothcore();

// Registers the C++ azerothcore module into Python's internal table of built-in
// modules before the interpreter starts. This allows Python scripts to import
// and use C++ functionality via import azerothcore.
void InitAzerothCoreModule()
{
    if (PyImport_AppendInittab("azerothcore", PyInit_azerothcore) == -1)
        throw std::runtime_error("Failed to append azerothcore module to inittab");
}

// Forward declare the init function created by the macro below
// This macro expands to PyInit_azerothcore (for Python 3)
BOOST_PYTHON_MODULE(azerothcore)
{
    // Global wrapper
    // Usage: ac.Register("PLAYER_LOGIN", on_login)
    bp::def("Register", +[](const char* eventName, PythonAPI::Object callback)
    {
        if (sPythonEngine->IsEnabled())
            sPythonEngine->RegisterHook(std::string(eventName), callback);
    });

    // Entry specific wrapper
    // Usage: ac.Register("CREATURE_ADD_WORLD", on_add_world, 12345)
    bp::def("Register", +[](const char* eventName, PythonAPI::Object callback, uint32 entryId)
    {
        if (sPythonEngine->IsEnabled())
            sPythonEngine->RegisterHook(std::string(eventName), callback, entryId);
    });

    export_constants();

    bp::class_<Unit, boost::noncopyable>("Unit", bp::no_init)
        .def("GetName", &Unit::GetName, bp::return_value_policy<bp::copy_const_reference>())
        .def("GetLevel", &Unit::GetLevel)
        .def("GetHealth", &Unit::GetHealth)
        .def("SetHealth", &Unit::SetHealth)
        .def("GetMaxHealth", &Unit::GetMaxHealth)
        .def("GetRace", &Unit::getRace, bp::args("original") = false)
        .def("GetClass", &Unit::getClass)
        .def("GetGender", &Unit::getGender)
        .def("GetGUID", &PythonUnitMethods::GetGUIDLow);

    bp::class_<Player, bp::bases<Unit>, boost::noncopyable>("Player", bp::no_init)
        .def("Say", &PythonPlayerMethods::Say)
        .def("AddItem", &PythonPlayerMethods::AddItem)
        .def("SendSysMessage", &PythonPlayerMethods::SendSysMessage);

    bp::class_<Creature, bp::bases<Unit>, boost::noncopyable>("Creature", bp::no_init)
        .def("GetEntry", &Creature::GetEntry)
        .def("Respawn", &PythonCreatureMethods::Respawn)
        .def("SetHome", &PythonCreatureMethods::SetHomePosition)
        .def("GetGUID", &PythonCreatureMethods::GetGUIDLow);

    bp::class_<GameObject, boost::noncopyable>("GameObject", bp::no_init)
        .def("GetEntry", &GameObject::GetEntry)
        .def("GetName", &GameObject::GetName, bp::return_value_policy<bp::copy_const_reference>())
        .def("Respawn", &PythonGameObjectMethods::Respawn)
        .def("Use", &PythonGameObjectMethods::Use)
        .def("GetGUID", &PythonGameObjectMethods::GetGUIDLow);
}
