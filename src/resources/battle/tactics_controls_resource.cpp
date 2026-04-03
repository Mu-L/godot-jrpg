#include "tactics_controls_resource.hpp"
#include "core/constants.hpp"
#include "entity/battle/tactics_pawn.hpp"
#include "entity/battle/tactics_player.hpp"

tog::TacticsControlsResource::TacticsControlsResource() {
    m_actions["Move"] = "player_wants_to_move";
    m_actions["Wait"] = "player_wants_to_wait";
    m_actions["Cancel"] = "player_wants_to_cancel";
    m_actions["Attack"] = "player_wants_to_attack";
    m_actions["Debug_next_turn"] = "player_wants_to_skip_turn";
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

void tog::TacticsControlsResource::_bind_methods() {
     //bind property to editor
     rl::bind_property(TacticsControlsResource, is_joystick, bool);
     rl::bind_property(TacticsControlsResource, input_hints_folded, bool);

     //Signal emitted when the actions menu visibility needs to be set
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_set_actions_menu_visibility>::add<bool, tog::TacticsPawn*>();
     //Signal emitted when the camera needs to be moved.
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_move_camera>::add<float>();
     //Signal emitted when a pawn needs to be selected
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_select_pawn>::add<tog::TacticsPlayer*>();
     //Signal emitted when a pawn needs to be selected for attack
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_select_pawn_to_attack>::add<>();
     //Signal emitted when a new location needs to be selected
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_select_new_location>::add<>();
     //Signal emitted when the cursor shape needs to be set to "move"
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_move>::add<>();
     //Signal emitted when the cursor shape needs to be set to "arrow"
     rl::signal_binding<TacticsControlsResource, tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_arrow>::add<>();
 }


