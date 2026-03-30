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
    
}
