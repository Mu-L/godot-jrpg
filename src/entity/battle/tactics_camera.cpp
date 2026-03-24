#include "tactics_camera.hpp"

void tog::TacticsCamera::_ready() {
    //Get respective nodes
    m_t_pivot = this->get_node<godot::Node3D>(tog::node::name::BattleTest::TwistPivot);
    m_p_pivot = this->get_node<godot::Node3D>(tog::node::name::BattleTest::PitchPivot);
    m_camera = this->get_node<godot::Camera3D>(tog::node::name::BattleTest::Camera3D);

    //Initialize camera service
    m_tactics_camera_service = tog::TacticsCameraService::reset(m_tactics_camera_resource, m_tactics_control_resource);
    assertion(m_tactics_camera_service, "Tactics Camera Service static object did not initalize ");
    //Set up camera service
    m_tactics_camera_service->setup(this, m_camera);
    //Set the initial boundary center
    m_tactics_camera_resource->m_boundry_center = get_global_position();

    //Connect signals
    rl::signal<tog::node::signal::TacticsCameraResource::called_rotate_camera>::connect<tog::TacticsCameraResource>(m_tactics_camera_resource) <=> signal_callback(this, rotate_camera);
    rl::signal<tog::node::signal::TacticsCameraResource::called_move_camera>::connect<tog::TacticsCameraResource>(m_tactics_camera_resource) <=> signal_callback(this, move_camera);
}

void tog::TacticsCamera::_process(double p_delta) {
    m_tactics_camera_service->process(static_cast<float>(p_delta), this);
}

void tog::TacticsCamera::move_camera(float h, float v, bool joystick, float delta) {
    m_tactics_camera_service->m_tactics_camera_movement_service->move_camera(h, v, joystick, delta, this);
}

void tog::TacticsCamera::rotate_camera(float delta, int twist) {
    m_tactics_camera_resource->m_is_rotating = true;
    m_tactics_camera_service->m_tactics_camera_rotation_service->add_angle_to_horizontal_rotation(twist);
    m_tactics_camera_service->m_tactics_camera_rotation_service->rotate_camera(delta, m_t_pivot, m_p_pivot);
}

void tog::TacticsCamera::free_look(float delta) {
    m_tactics_camera_service->m_tactics_camera_rotation_service->free_look(delta, m_t_pivot, m_p_pivot);
}

void tog::TacticsCamera::zoom_camera(float zoom_increment) {
    m_tactics_camera_service->m_tactics_zoom_service->zoom_camera(zoom_increment);
}

void tog::TacticsCamera::reset_cam_zoom() {
    m_tactics_camera_service->m_tactics_zoom_service->reset_camera_zoom(this, m_camera);
}


