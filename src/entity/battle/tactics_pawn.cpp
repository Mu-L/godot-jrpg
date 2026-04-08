#include "tactics_pawn.hpp"

#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/ray_cast3d.hpp"

void tog::TacticsPawn::_ready() {
    auto resource_loader = godot::ResourceLoader::get_singleton();
    m_tactics_controls_resource = resource_loader->load(tog::path::resource::battle::tactics_control_resource);
    m_stats_node = get_node<tog::Stats>(tog::node::name::BattleTest::Stats);
    if (m_stats_node) { m_expertise = m_stats_node->m_expertise; }
    m_tactics_pawn_sprite = get_node<tog::TacticsPawnSprite>(tog::node::name::BattleTest::Character);
    m_tactics_pawn_resource = memnew(tog::TacticsPawnResource);
    m_tactics_pawn_service = memnew(tog::TacticsPawnService);
    m_tactics_pawn_service->setup(this);
    m_tactics_controls_resource->set_actions_menu_visibility(false, this);
    show_pawn_stats(false);
}

void tog::TacticsPawn::_physics_process(double p_delta) {
    m_tactics_pawn_service->process(this, p_delta);
}

bool tog::TacticsPawn::center() {
    return m_tactics_pawn_sprite->adjust_to_center(this);
}

void tog::TacticsPawn::show_pawn_stats(bool v) {
    if (auto node = get_node<godot::Node3D>(tog::node::name::BattleTest::CharacterUI); node) {
        node->set_visible(v);
    }
}

tog::TacticsTile* tog::TacticsPawn::get_tile() const {
    return rl::gdcast<TacticsTile>(get_node<godot::RayCast3D>(tog::node::name::BattleTest::Tile)->get_collider());
}

bool tog::TacticsPawn::is_alive() {
    return m_stats_node->m_current_health > 0;
}

bool tog::TacticsPawn::can_pawn_move() {
    return ( m_tactics_pawn_resource->m_can_move && is_alive() );
}

bool tog::TacticsPawn::can_pawn_attack() {
    return ( m_tactics_pawn_resource->m_can_attack && is_alive() );
}

bool tog::TacticsPawn::can_act() {
    return ( (m_tactics_pawn_resource->m_can_move || m_tactics_pawn_resource->m_can_attack) && is_alive() );
}

void tog::TacticsPawn::reset_turn() {
    m_tactics_pawn_resource->reset_turn();
}

void tog::TacticsPawn::end_pawn_turn() {
    m_tactics_pawn_resource->end_pawn_turn();
}

bool tog::TacticsPawn::attack_target_pawn(tog::TacticsPawn* target_pawn, float delta) {
    return m_tactics_pawn_service->attack_target_pawn(this, target_pawn, delta);
}

void tog::TacticsPawn::move_along_path(float delta) {
    m_tactics_pawn_service->m_tactics_pawn_movement_service->move_along_path(this, delta);
}
