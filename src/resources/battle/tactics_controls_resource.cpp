 #include "tactics_controls_resource.hpp"

 tog::TacticsControlsResource::TacticsControlsResource() {
    m_actions["Move"] = "_player_wants_to_move";
    m_actions["Wait"] = "_player_wants_to_wait";
    m_actions["Cancel"] = "_player_wants_to_cancel";
    m_actions["Attack"] = "_player_wants_to_attack";
    m_actions["Debug_next_turn"] = "_player_wants_to_skip_turn";
}

void tog::TacticsControlsResource::set_actions_menu_visibility(bool visible, TacticsPawn* pawn) {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_set_actions_menu_visibility, visible, pawn);
}

void tog::TacticsControlsResource::move_camera(float delta) {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_move_camera, delta);
}

void tog::TacticsControlsResource::select_pawn(TacticsPlayer* player) {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_select_pawn, player);
}

void tog::TacticsControlsResource::select_pawn_to_attack() {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_select_pawn_to_attack);
}

void tog::TacticsControlsResource::select_new_location() {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_select_new_location);
}

void tog::TacticsControlsResource::set_cursor_shape_to_move() {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_move);
}

void tog::TacticsControlsResource::set_cursor_shape_to_arrow() {
    this->emit_signal(tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_arrow);
}


