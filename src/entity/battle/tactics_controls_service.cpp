#include "tactics_controls_service.hpp"

tog::TacticsControlsService::TacticsControlsService(const godot::Ref<tog::TacticsControlsResource>& tactics_controls_resource,
                                                    const godot::Ref<tog::TacticsCameraResource>& tactics_camera_resource,
                                                    const godot::Ref<tog::TacticsParticipantResource>& tactics_participant_resource,
                                                    const godot::Ref<tog::TacticsArenaResource>& tactics_arena_resource,
                                                    godot::Node* input_capture) {
    m_tactics_controls_resource = tactics_controls_resource;
    m_tactics_camera_resource = tactics_camera_resource;
    m_tactics_participant_resource = tactics_participant_resource;
    m_tactics_arena_resource = tactics_arena_resource;
    m_input_capture = input_capture;
    m_tactics_controls_input_service = memnew(tog::TacticsControlsInputService(m_tactics_controls_resource, m_input_capture));
    m_tactics_ui_service = memnew(tog::TacticsUIService(m_tactics_controls_resource));
    m_tactics_controls_camera_service = memnew(tog::TacticsControlsCameraService(m_tactics_camera_resource));
    m_tactics_controls_selection_service = memnew(
        tog::TacticsControlsSelectionService(
            m_tactics_participant_resource,
            m_tactics_arena_resource,
            m_tactics_controls_resource,
            m_tactics_camera_resource,
            m_tactics_controls_input_service
        )
    );
}

void tog::TacticsControlsService::setup(tog::TacticsControls* tactics_controls) {
    if (!m_tactics_controls_resource.is_null()) {
        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_set_actions_menu_visibility,
            callable_mp(tactics_controls, &tog::TacticsControls::set_actions_menu_visibility)
        );

        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_set_cursor_shape_to_move,
            callable_mp(tactics_controls, &tog::TacticsControls::set_cursor_shape_to_arrow)
        );

        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_set_cursor_shape_to_arrow,
            callable_mp(tactics_controls, &tog::TacticsControls::set_cursor_shape_to_arrow)
        );

        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_select_pawn,
            callable_mp(tactics_controls, &tog::TacticsControls::select_pawn)
        );

        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_select_pawn_to_attack,
            callable_mp(tactics_controls, &tog::TacticsControls::select_pawn_to_attack)
        );

        m_tactics_controls_resource->connect(
            tog::constants::node::signal::TacticsControlResource::called_select_new_location,
            callable_mp(tactics_controls, &tog::TacticsControls::select_new_location)
        );
    }
}

void tog::TacticsControlsService::physics_process(float delta, tog::TacticsControls* tactics_controls) {
    m_tactics_controls_input_service->update_mouse_mode();
    m_tactics_ui_service->update_controller_hints(tactics_controls);
}

void tog::TacticsControlsService::handle_input(const godot::Ref<godot::InputEvent>& event) {
    m_tactics_controls_input_service->handle_input(event);
}

void tog::TacticsControlsService::set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn, tog::TacticsControls* tactics_controls) {
    m_tactics_ui_service->set_actions_menu_visibility(v, tactics_pawn, tactics_controls);
}

void tog::TacticsControlsService::select_pawn(tog::TacticsPlayer* tactics_player, tog::TacticsControls* tactics_controls) {
    m_tactics_controls_selection_service->select_pawn(tactics_player, tactics_controls);
}

void tog::TacticsControlsService::select_new_location(tog::TacticsControls* tactics_controls) {
    m_tactics_controls_selection_service->select_new_location(tactics_controls);
}

void tog::TacticsControlsService::select_pawn_to_attack(tog::TacticsControls* tactics_controls) {
    m_tactics_controls_selection_service->select_pawn_to_attack(tactics_controls);
}

void tog::TacticsControlsService::player_wants_to_move() {
    m_tactics_controls_selection_service->player_wants_to_move();
}

void tog::TacticsControlsService::player_wants_to_cancel() {
    m_tactics_controls_selection_service->player_wants_to_cancel();
}

void tog::TacticsControlsService::player_wants_to_wait() {
    m_tactics_controls_selection_service->player_wants_to_wait();

}

void tog::TacticsControlsService::player_wants_to_skip_turn() {
    m_tactics_controls_selection_service->player_wants_to_skip_turn();
}

void tog::TacticsControlsService::player_wants_to_attack() {
    m_tactics_controls_selection_service->player_wants_to_attack();
}


