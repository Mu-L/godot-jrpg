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

tog::TacticsTile* tog::TacticsPawn::get_tile() const {
    return rl::gdcast<TacticsTile>(get_node<godot::RayCast3D>(tog::node::name::BattleTest::Tile)->get_collider());
}
