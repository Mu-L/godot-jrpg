#include "tactics_participant.hpp"

#include "tactics_arena.hpp"
#include "tactics_player.hpp"
#include "tactics_opponent.hpp"
#include "tactics_participant_service.hpp"

#include "core/constants.hpp"

#include "resources/battle/tactics_participant_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/resource_loader.hpp"

void tog::TacticsParticipant::_ready() {
    godot::ResourceLoader* resource_loader = godot::ResourceLoader::get_singleton();
    m_tactics_participant_resource = resource_loader->load(tog::path::resource::battle::tactics_participant_resource);
    m_tactics_camera_resource = resource_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_controls_resource = resource_loader->load(tog::path::resource::battle::tactics_control_resource);
    m_tactics_arena = godot::Object::cast_to<tog::TacticsArena>(get_node_or_null(tog::node::name::BattleTest::TacticsArena));
    m_tactics_player = godot::Object::cast_to<tog::TacticsPlayer>(get_node_or_null(tog::node::name::BattleTest::TacticsPlayer));
    m_tactics_opponent = godot::Object::cast_to<tog::TacticsOpponent>(get_node_or_null(tog::node::name::BattleTest::TacticsOpponent));

    //Initialize the service with necessary resources
    m_tactics_participant_service = memnew(tog::TacticsParticipantService(m_tactics_participant_resource, m_tactics_camera_resource, m_tactics_controls_resource));
    m_tactics_participant_service->setup(this);

    //Connect the skip_turn signal to the skip_turn method
    this->connect(tog::node::signal::TacticsParticipantResource::called_skip_turn, callable_mp(this, &tog::TacticsParticipant::skip_turn));
}

void tog::TacticsParticipant::act(float delta, bool is_player, godot::Node3D* parent) {
    m_tactics_participant_service->act(delta, is_player, parent, this);
}

void tog::TacticsParticipant::configure(const godot::Ref<tog::TacticsCameraResource>& camera_resource, const godot::Ref<tog::TacticsControlsResource>& controls_resource) {
    m_tactics_participant_service->configure(camera_resource, controls_resource);
}

bool tog::TacticsParticipant::is_configured(godot::Node3D* parent) {
    m_tactics_participant_service->is_configured(parent);
}

bool tog::TacticsParticipant::can_act(godot::Node3D* parent) {
    m_tactics_participant_service->can_act(parent);
}

void tog::TacticsParticipant::reset_turn(godot::Node3D* parent) {
    m_tactics_participant_service->reset_turn(parent);
}

void tog::TacticsParticipant::skip_turn() {
    m_tactics_participant_service->skip_turn(m_tactics_player);
}
