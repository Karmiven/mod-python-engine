#include "PythonHeaders.h"
#include "Position.h"

namespace bp = boost::python;

/**
 * @brief Position struct - 3D coordinates with orientation
 */
void export_position_struct()
{
    bp::class_<Position> position_struct("Position", bp::no_init);

    // coordinates and orientation
    position_struct.def("GetPositionX", &Position::GetPositionX);
    position_struct.def("GetPositionY", &Position::GetPositionY);
    position_struct.def("GetPositionZ", &Position::GetPositionZ);
    position_struct.def("GetOrientation", &Position::GetOrientation);

    // distance helpers
    position_struct.def("GetExactDist2d",
                        static_cast<float (Position::*)(float, float) const>(&Position::GetExactDist2d));
    position_struct.def("GetExactDist",
                        static_cast<float (Position::*)(float, float, float) const>(&Position::GetExactDist));
    position_struct.def("GetExactDist2dSq",
                        static_cast<float (Position::*)(float, float) const>(&Position::GetExactDist2dSq));
    position_struct.def("GetExactDistSq",
                        static_cast<float (Position::*)(float, float, float) const>(&Position::GetExactDistSq));
    position_struct.def("GetExactDist2dTo",
                        static_cast<float (Position::*)(Position const&) const>(&Position::GetExactDist2d));
    position_struct.def("GetExactDistTo",
                        static_cast<float (Position::*)(Position const&) const>(&Position::GetExactDist));
    position_struct.def("GetExactDist2dSqTo",
                        static_cast<float (Position::*)(Position const&) const>(&Position::GetExactDist2dSq));
    position_struct.def("GetExactDistSqTo",
                        static_cast<float (Position::*)(Position const&) const>(&Position::GetExactDistSq));

    // angle helpers
    position_struct.def("GetAngle", static_cast<float (Position::*)(float, float) const>(&Position::GetAngle));

    // validity
    position_struct.def("IsPositionValid", &Position::IsPositionValid);
}

/**
 * @brief WorldLocation class - Position with map context
 * @note Inherits from Position
 */
void export_worldlocation_class()
{
    bp::class_<WorldLocation, bp::bases<Position>> worldlocation_class("WorldLocation", bp::no_init);

    // map id accessors
    worldlocation_class.def("GetMapId", &WorldLocation::GetMapId);
    worldlocation_class.def("SetMapId", &WorldLocation::SetMapId);
}
