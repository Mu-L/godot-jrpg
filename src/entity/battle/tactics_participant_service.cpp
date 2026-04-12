#include "tactics_participant_service.hpp"

#include "tactics_player.hpp"
#include "tactics_participant_turn_service.hpp"
#include "tactics_participant_combat_service.hpp"
#include "resources/battle/tactics_participant_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

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

void tog::TacticsParticipantService::configure(const godot::Ref<tog::TacticsCameraResource>& camera_resource, const godot::Ref<tog::TacticsControlsResource>& controls_resource) {
    m_tactics_camera_resource = camera_resource;
    m_tactics_controls_resource = controls_resource;
}

bool tog::TacticsParticipantService::is_configured(godot::Node3D* parent) {
    return parent->

}

bool tog::TacticsParticipantService::can_act(godot::Node3D* parent) {
}

void tog::TacticsParticipantService::reset_turn(godot::Node3D* parent) {

}

void tog::TacticsParticipantService::skip_turn(tog::TacticsPlayer* tactics_player) {

}
