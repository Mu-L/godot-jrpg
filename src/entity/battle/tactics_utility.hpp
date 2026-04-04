#pragma once
#include "godot_cpp/variant/vector3.hpp"

//remove the y value for a godot::Vector3 object
inline godot::Vector3 remove_y(const godot::Vector3 vec) {
    return vec * godot::Vector3(1, 0, 1);
}

//Calculates a Vector3 distance, removing the Y value from the result
inline float distance_without_y(godot::Vector3 a, godot::Vector3 b) {
    return remove_y(b).distance_to(remove_y(a));
}



