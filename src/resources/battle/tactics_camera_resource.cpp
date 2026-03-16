#include "tactics_camera_resource.hpp"

void tog::TacticsCameraResource::move_camera(float h, float v, bool joystick, float delta) {
    this->emit_signal(tog::node::signal::TacticsCameraResource::called_move_camera, h, v, joystick, delta);
}

void tog::TacticsCameraResource::rotate_camera(float delta, float twist) {
    this->emit_signal(tog::node::signal::TacticsCameraResource::called_rotate_camera, delta, twist);
}

void tog::TacticsCameraResource::free_look(float delta) {
    this->emit_signal(tog::node::signal::TacticsCameraResource::called_free_look, delta);
}
