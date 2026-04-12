#include "tactics_participant_service.hpp"

#include "tactics_player.hpp"

tog::TacticsParticipantService::TacticsParticipantService(
    const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
    const godot::Ref<tog::TacticsCameraResource>& camera_resource,
    const godot::Ref<tog::TacticsControlsResource>& controls_resource)
        : m_tactics_participant_resource{participant_resource},
          m_tactics_camera_resource{camera_resource},
          m_tactics_controls_resource{controls_resource} {
    //initializes the TacticsParticipantService
    m_tactics_participant_turn_service = memnew(
        tog::TacticsParticipantTurnService(m_tactics_participant_resource, m_tactics_camera_resource, m_tactics_controls_resource)
    );
    m_tactics_combat_service = memnew(
        tog::TacticsParticipantCombatService(m_tactics_participant_resource, m_tactics_camera_resource, m_tactics_controls_resource)
    );
}

void tog::TacticsParticipantService::setup(tog::TacticsParticipant* tactics_participant) {
    //this is just a check to see if the resources are empty
}

void tog::TacticsParticipantService::act(float delta, bool is_player, godot::Node3D* parent, tog::TacticsParticipant* tactics_participant) {
    if (is_player) {
        tog::TacticsPlayer* player = godot::Object::cast_to<tog::TacticsPlayer>(parent);
        m_tactics_participant_turn_service->handle_player_turn(delta, player, tactics_participant);
    }
}
