#include "tactics_arena.hpp"

void tog::TacticsArena::_ready() {
    auto resource_loader = godot::ResourceLoader::get_singleton();
    m_tactics_arena_resource = resource_loader->load(tog::path::resource::battle::tactics_arena_resource);
    m_tactics_arena_service = memnew(tog::TacticsArenaService(m_tactics_arena_resource));
    m_tactics_arena_service->setup(this);
}

void tog::TacticsArena::reset_all_tile_markers() {
    m_tactics_arena_service->reset_all_tile_markers(this);
}

void tog::TacticsArena::configure_tiles() {
    m_tactics_arena_service->configure_tiles(this);
}

void tog::TacticsArena::process_surrounding_tiles(tog::TacticsTile* root_tile, float height, godot::Array allies_on_map) {
    m_tactics_arena_service->process_surrounding_tiles(root_tile, height, allies_on_map);
}

godot::Array tog::TacticsArena::get_pathfinding_tilestack(tog::TacticsTile* to) {
    m_tactics_arena_service->get_pathfinding_tilestack(to);
}

void tog::TacticsArena::get_nearest_target_adjacent_tile(tog::TacticsPawn* tactics_pawn, godot::Array target_pawns) {
    m_tactics_arena_service->get_nearest_target_adjacent_tile(tactics_pawn, target_pawns);
}

tog::TacticsPawn* tog::TacticsArena::get_weakest_attackable_pawn(godot::Array pawns) {
    return m_tactics_arena_service->get_weakest_attackable_pawn(pawns);
}

void tog::TacticsArena::mark_hover_tile(tog::TacticsTile* tactics_tile) {
    m_tactics_arena_service->mark_hover_tile(this, tactics_tile);
}

void tog::TacticsArena::mark_reachable_tiles(tog::TacticsTile* root_tile, float distance) {
    m_tactics_arena_service->mark_reachable_tiles(this, root_tile, distance);
}

void tog::TacticsArena::mark_attackable_tiles(tog::TacticsTile* root_tile, float distance) {
    m_tactics_arena_service->mark_attackable_tiles(this, root_tile, distance);
}
