#pragma once
#include "godot_cpp/variant/vector3.hpp"

inline godot::Vector3 get_zero_vector3() {
    return{0, 0, 0};
}

inline godot::Vector3 get_one_vector3() {
    return{1, 1, 1};
}

//Left unit vector. Represents the local direction of left, and the global direction of west.
inline godot::Vector3 get_left_vector3() {
    return{-1, 0, 0};
}

//Right unit vector. Represents the local direction of right, and the global direction of east.
inline godot::Vector3 get_right_vector3() {
    return{1, 0, 0};
}

inline godot::Vector3 get_up_vector3() {
    return{0, 1, 0};
}

inline godot::Vector3 get_down_vector3() {
    return{0, -1, 0};
}

//Forward unit vector. Represents the local direction of forward, and the global direction of north.
//Keep in mind that the forward direction for lights, cameras, etc is different from 3D assets like characters, which face towards the camera by convention.
inline godot::Vector3 get_forward_vector3() {
    return{0, 0, -1};
}

//Back unit vector. Represents the local direction of back, and the global direction of south.
inline godot::Vector3 get_back_vector3() {
    return{0, 0, 1};
}