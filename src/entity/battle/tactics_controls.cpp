#include "tactics_controls.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/resource_loader.hpp"

void tog::TacticsControls::_ready() {
    const auto res_loader = godot::ResourceLoader::get_singleton();
    m_tactics_control_resource = res_loader->load(tog::path::resource::battle::tactics_control_resource);
    m_tactics_camera_resource = res_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_participant_resource = res_loader->load(tog::path::resource::battle::tactics_participant_resource);
    m_tactics_arena_resource = res_loader->load(tog::path::resource::battle::tactics_arena_resource);

    m_tactics_pawn = nullptr;

    m_input_capture = get_node<tog::InputCapture>(tog::constants::node::name::BattleTest::InputCapture);

    m_tactics_control_service = memnew(tog::TacticsControlsService(m_tactics_control_resource, m_tactics_camera_resource, m_tactics_participant_resource, m_tactics_arena_resource, m_input_capture));
    m_tactics_control_service->setup(this);

    //Connect action buttons to their respective methods
    for (godot::String action : m_tactics_control_resource->m_actions.keys()) {
        godot::String value = m_tactics_control_resource->m_actions[action];
        this->get_action(action)->connect(tog::node::signal::BaseButton::pressed, godot::Callable(this, value));
    }
}

void tog::TacticsControls::_physics_process(double p_delta) {
    //m_tactics_control_service->
}

void tog::TacticsControls::_input(const godot::Ref<godot::InputEvent> &p_event) {

}

void tog::TacticsControls::set_cursor_shape_to_move() {

}

void tog::TacticsControls::set_cursor_shape_to_arrow() {

}

void tog::TacticsControls::move_camera(float delta) {

}

godot::Button* tog::TacticsControls::get_action(const godot::String &action) {
    return {};
}

bool tog::TacticsControls::is_mouse_hovering_ui_elem() {
    return false;
}

void tog::TacticsControls::set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn) {
}

godot::Object* tog::TacticsControls::get_3d_canvas_mouse_position(int collision_mask) {

    return {};
}

void tog::TacticsControls::select_pawn(tog::TacticsPlayer* tactics_player) {

}

void tog::TacticsControls::select_new_location() {
}

void tog::TacticsControls::select_pawn_to_attack() {
}

void tog::TacticsControls::player_wants_to_move() {
}

void tog::TacticsControls::player_wants_to_cancel() {
}

void tog::TacticsControls::player_wants_to_wait() {
}

void tog::TacticsControls::player_wants_to_skip_turn() {
}

void tog::TacticsControls::player_wants_to_attack() {
}

//let godot be aware about the
void tog::TacticsControls::_bind_methods() {
    //make godot engine be aware about these functions

    rl::bind_member_function(TacticsControls, player_wants_to_move);
    rl::bind_member_function(TacticsControls, player_wants_to_wait);
    rl::bind_member_function(TacticsControls, player_wants_to_cancel);
    rl::bind_member_function(TacticsControls, player_wants_to_attack);
    rl::bind_member_function(TacticsControls, player_wants_to_skip_turn);
    rl::bind_member_function(TacticsControls, set_actions_menu_visibility);

    rl::bind_member_function(TacticsControls, set_cursor_shape_to_move);
    rl::bind_member_function(TacticsControls, set_cursor_shape_to_arrow);
    rl::bind_member_function(TacticsControls, select_pawn);
    rl::bind_member_function(TacticsControls, select_pawn_to_attack);
    rl::bind_member_function(TacticsControls, select_new_location);
}
