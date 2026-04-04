#include "tactics_pawn.hpp"

#include "godot_cpp/classes/ray_cast3d.hpp"

void tog::TacticsPawn::_ready() {
    m_stats_node = get_node<tog::Stats>(tog::node::name::BattleTest::Stats);
    m_tactics_pawn_sprite = get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character);
    if (m_stats_node) {
        m_expertise = m_stats_node->m_expertise;
    }
    m_tactics_controls_resource = memnew(tog::TacticsControlsResource);
    m_tactics_pawn_service = memnew(tog::TacticsPawnService);
    //todo: finish this
    //m_tactics_pawn_service->setup()
}

void tog::TacticsPawn::_physics_process(double p_delta) {

}

bool tog::TacticsPawn::center() {

}

void tog::TacticsPawn::show_pawn_stats(bool v) {

}

tog::TacticsTile* tog::TacticsPawn::get_tile() const {
    return rl::gdcast<TacticsTile>(get_node<godot::RayCast3D>(tog::node::name::BattleTest::Tile)->get_collider());
}

bool tog::TacticsPawn::is_alive() {

}

bool tog::TacticsPawn::can_pawn_move() {

}

bool tog::TacticsPawn::can_pawn_attack() {

}

bool tog::TacticsPawn::can_act() {

}

void tog::TacticsPawn::reset_turn() {

}

void tog::TacticsPawn::end_pawn_turn() {

}

bool tog::TacticsPawn::attack_target_pawn(tog::TacticsPawn *target_pawn, float delta) {

}

void tog::TacticsPawn::move_along_path(float delta) {

}
