#include "tactics_participant_resource.hpp"

void tog::TacticsParticipantResource::skip_turn() {
    this->emit_signal(tog::node::signal::TacticsParticipantResource::called_skip_turn);
}
