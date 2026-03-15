#include "tactics_pawn_resource.hpp"

void tog::TacticsPawnResource::reset_turn() {
    m_can_move = true;
    m_can_attack = true;
}

void tog::TacticsPawnResource::end_pawn_turn() {
    m_can_move = false;
    m_can_attack = false;
    this->emit_signal(tog::node::signal::TacticsPawnResource::turn_ended);
}

void tog::TacticsPawnResource::set_moving(bool value) {
    m_is_moving = value;
    if (value)
        this->emit_signal(tog::node::signal::TacticsPawnResource::pawn_moved);
}

void tog::TacticsPawnResource::set_attacking(bool value) {
    m_can_attack = value;
    if (!value)
        this->emit_signal(tog::node::signal::TacticsPawnResource::pawn_attacked);
}
