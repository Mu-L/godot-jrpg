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
        ));
}

void tog::TacticsControlsService::setup(tog::TacticsControls* tactics_controls) {
    //m_tactics_controls_resource->connect(tog::node::signal::TacticsControlResource::called_set_actions_menu_visibility, callable_mp(tactics_controls, tactics_controls))
}