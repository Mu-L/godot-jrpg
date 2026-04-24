#include "tactics_participant_resource.hpp"

void tog::TacticsParticipantResource::skip_turn() {
    this->emit_signal(tog::node::signal::TacticsParticipantResource::called_skip_turn);
}

void tog::TacticsParticipantResource::_bind_methods() {
    //Signal emitted when a turn is skipped
    ADD_SIGNAL(godot::MethodInfo(tog::node::signal::TacticsParticipantResource::called_skip_turn));
}
