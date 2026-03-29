#include "tactics_controls_selection_service.hpp"

tog::TacticsControlsSelectionService::TacticsControlsSelectionService(
    const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
    const godot::Ref<tog::TacticsArenaResource>& arena_resource,
    const godot::Ref<tog::TacticsControlsResource>& controls_resource,
    const godot::Ref<tog::TacticsCameraResource>& camera_resource,
    const godot::Ref<tog::TacticsControlsInputService>& controls_input_service) {
    m_tactics_participant_resource = participant_resource;
    m_tactics_arena_resource = arena_resource;
    m_tactics_controls_resource = controls_resource;
    m_tactics_camera_resource = camera_resource;
    m_tactics_controls_input_service = controls_input_service;
}

void tog::TacticsControlsSelectionService::select_pawn(tog::TacticsPlayer* tactics_player, tog::TacticsControls* tactics_controls) {
    //m_tactics_arena_resource->reset_all_tile_markers();

    if (tactics_controls->m_tactics_pawn) {
        //tactics_controls->
    }

}
