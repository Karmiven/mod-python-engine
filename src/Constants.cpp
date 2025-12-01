#include "PythonHeaders.h"
#include "SharedDefines.h"

void export_constants()
{
    using namespace boost::python;

    // enum Gender
    enum_<Gender>("Gender")
        .value("Male", GENDER_MALE)
        .value("Female", GENDER_FEMALE)
        .value("None", GENDER_NONE)
        .export_values();

    // enum Races
    enum_<Races>("Race")
        .value("Human", RACE_HUMAN)
        .value("Orc", RACE_ORC)
        .value("Dwarf", RACE_DWARF)
        .value("NightElf", RACE_NIGHTELF)
        .value("Undead", RACE_UNDEAD_PLAYER)
        .value("Tauren", RACE_TAUREN)
        .value("Gnome", RACE_GNOME)
        .value("Troll", RACE_TROLL)
        .value("BloodElf", RACE_BLOODELF)
        .value("Draenei", RACE_DRAENEI)
        .export_values();

    // enum Classes
    enum_<Classes>("Class")
        .value("Warrior", CLASS_WARRIOR)
        .value("Paladin", CLASS_PALADIN)
        .value("Hunter", CLASS_HUNTER)
        .value("Rogue", CLASS_ROGUE)
        .value("Priest", CLASS_PRIEST)
        .value("DeathKnight", CLASS_DEATH_KNIGHT)
        .value("Shaman", CLASS_SHAMAN)
        .value("Mage", CLASS_MAGE)
        .value("Warlock", CLASS_WARLOCK)
        .value("Druid", CLASS_DRUID)
        .export_values();
}
