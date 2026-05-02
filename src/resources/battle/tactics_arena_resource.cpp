#include "tactics_arena_resource.hpp"

void tog::TacticsArenaResource::reset_all_tile_markers() {
    this->emit_signal(tog::node::signal::TacticsArenaResource::called_reset_all_tile_markers);
}

godot::Array tog::TacticsArenaResource::get_pathfinding_tilestack(tog::TacticsTile* tile) {
    m_logger->log()->print("Called: godot::Array tog::TacticsArenaResource::get_pathfinding_tilestack(tog::TacticsTile* tile)");
    m_logger->log()->print("size of m_path_tiles_stack BEFORE is {}", m_path_tiles_stack.size());
    this->emit_signal(tog::node::signal::TacticsArenaResource::called_get_pathfinding_tilestack, tile);
    m_logger->log()->print("size of m_path_tiles_stack AFTER is {}", m_path_tiles_stack.size());
    return m_path_tiles_stack;
}

void tog::TacticsArenaResource::mark_hover_tile(tog::TacticsTile* tile) {
    this->emit_signal(tog::node::signal::TacticsArenaResource::called_mark_hover_tile, tile);
}

void tog::TacticsArenaResource::_bind_methods() {
    //Emitted when all tile markers need to be reset
    rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_reset_all_tile_markers>::add<>();

    //Emitted when pathfinding tilestack is requested - The target tile for pathfinding
    //rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_get_pathfinding_tilestack>::add<godot::Object*>();
    rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_get_pathfinding_tilestack>::add<tog::TacticsTile*>();

    //Emitted when a tile needs to be marked as hovered -  The tile to be marked as hovered
    //rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_mark_hover_tile>::add<godot::Object*>();
    rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_mark_hover_tile>::add<tog::TacticsTile*>();
}
