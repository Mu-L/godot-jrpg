#include "tactics_controls.hpp"

#include "cursor_service.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/resource_loader.hpp"

void tog::TacticsControls::_ready() {
    const auto resource_loader = godot::ResourceLoader::get_singleton();
    m_tactics_control_resource      = resource_loader->load(tog::path::resource::battle::tactics_control_resource);
    m_tactics_camera_resource       = resource_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_participant_resource  = resource_loader->load(tog::path::resource::battle::tactics_participant_resource);
    m_tactics_arena_resource        = resource_loader->load(tog::path::resource::battle::tactics_arena_resource);

    m_tactics_pawn = nullptr;

    m_input_capture = godot::Object::cast_to<tog::InputCapture>(get_node_or_null(tog::constants::node::name::BattleTest::InputCapture));

    m_tactics_control_service = memnew(tog::TacticsControlsService(m_tactics_control_resource, m_tactics_camera_resource, m_tactics_participant_resource, m_tactics_arena_resource, m_input_capture));
    m_tactics_control_service->setup(this);

    //Connect action buttons to their respective methods
    auto* attack_button = this->get_node<godot::Button>(tog::node::name::BattleTest::AttackButton);
    attack_button->connect(tog::node::signal::BaseButton::pressed, callable_mp(this, &TacticsControls::player_wants_to_attack));

    auto* move_button = this->get_node<godot::Button>(tog::node::name::BattleTest::MoveButton);
    move_button->connect(tog::node::signal::BaseButton::pressed, callable_mp(this, &TacticsControls::player_wants_to_move));

    auto* wait_button = this->get_node<godot::Button>(tog::node::name::BattleTest::WaitButton);
    wait_button->connect(tog::node::signal::BaseButton::pressed, callable_mp(this, &TacticsControls::player_wants_to_wait));

    auto* cancel_button = this->get_node<godot::Button>(tog::node::name::BattleTest::CancelButton);
    cancel_button->connect(tog::node::signal::BaseButton::pressed, callable_mp(this, &TacticsControls::player_wants_to_cancel));
}

void tog::TacticsControls::_physics_process(double p_delta) {
    //Handle physics-based processing
    m_tactics_control_service->physics_process(p_delta, this);
}

void tog::TacticsControls::_input(const godot::Ref<godot::InputEvent>& p_event) {
    m_tactics_control_service->handle_input(p_event);
}

void tog::TacticsControls::set_cursor_shape_to_move() {
    tog::CursorService::set_cursor_shape_to_move();
}

void tog::TacticsControls::set_cursor_shape_to_arrow() {
    tog::CursorService::set_cursor_shape_to_arrow();
}

void tog::TacticsControls::move_camera(float delta) {
    //todo: verify this function does not exist
    //m_tactics_control_service->move_camera(delta);
}

bool tog::TacticsControls::is_mouse_hovering_ui_elem() {
    //todo: verify this function does not exist
    //return m_tactics_control_service->is_mouse_hovering_ui_elem(this);
}

void tog::TacticsControls::set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn) {
    m_tactics_control_service->set_actions_menu_visibility(v, tactics_pawn, this);
}

godot::Object* tog::TacticsControls::get_3d_canvas_mouse_position(int collision_mask) {
    //todo: verify this function does not exist
    //return m_tactics_control_service->get_3d_canvas_mouse_position
    return nullptr;
}

void tog::TacticsControls::select_pawn(tog::TacticsPlayer* tactics_player) {
    m_tactics_control_service->select_pawn(tactics_player, this);
}

void tog::TacticsControls::select_new_location() {
    m_tactics_control_service->select_new_location(this);
}

void tog::TacticsControls::select_pawn_to_attack() {
    m_tactics_control_service->select_pawn_to_attack(this);
}

void tog::TacticsControls::player_wants_to_move() {
    m_tactics_control_service->player_wants_to_move();
}

void tog::TacticsControls::player_wants_to_cancel() {
    m_tactics_control_service->player_wants_to_cancel();
}

void tog::TacticsControls::player_wants_to_wait() {
    m_tactics_control_service->player_wants_to_wait();
}

void tog::TacticsControls::player_wants_to_skip_turn() {
    m_tactics_control_service->player_wants_to_skip_turn();
}

void tog::TacticsControls::player_wants_to_attack() {
    m_tactics_control_service->player_wants_to_attack();
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
