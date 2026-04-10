#include "tactics_arena_service.hpp"

#include "tactics_utility.hpp"
#include "core/constants.hpp"

void tog::TacticsArenaService::setup(tog::TacticsArena* tactics_arena) {
    if (m_tactics_arena_resource.is_valid()) {
        m_tactics_arena_resource->connect(
            tog::node::signal::TacticsArenaResource::called_reset_all_tile_markers,
            callable_mp(tactics_arena, &tog::TacticsArena::reset_all_tile_markers)
        );

        m_tactics_arena_resource->connect(
            tog::node::signal::TacticsArenaResource::called_get_pathfinding_tilestack,
            callable_mp(tactics_arena, &tog::TacticsArena::get_pathfinding_tilestack)
        );

        m_tactics_arena_resource->connect(
            tog::node::signal::TacticsArenaResource::called_mark_hover_tile,
            callable_mp(tactics_arena, &tog::TacticsArena::mark_hover_tile)
        );
    }
}

void tog::TacticsArenaService::reset_all_tile_markers(tog::TacticsArena* tactics_arena) {
    godot::TypedArray<godot::Node> tiles_nodes = tactics_arena->get_node<tog::TacticsTile>(tog::node::name::BattleTest::Tiles)->get_children();
    for (godot::Variant& variant : tiles_nodes) {
        if (auto tile_node = godot::Object::cast_to<tog::TacticsTile>(variant); tile_node) {
            tile_node->reset_markers();
        }
    }
}

void tog::TacticsArenaService::configure_tiles(tog::TacticsArena* tactics_arena) {
    TacticsTile* node = tactics_arena->get_node<tog::TacticsTile>(tog::node::name::BattleTest::Tiles);
    node->set_visible(true);
    tiles_into_static_bodies(node);
}

void tog::TacticsArenaService::process_surrounding_tiles(tog::TacticsTile* tactics_root_tile, float height, godot::Array allies_on_map) {
    godot::TypedArray<tog::TacticsTile> tactic_tile_process_queue;
    tactic_tile_process_queue.append(tactics_root_tile);


    while (!tactic_tile_process_queue.is_empty()) {
        tog::TacticsTile* current_tile = godot::Object::cast_to<tog::TacticsTile>(tactic_tile_process_queue.pop_front());

        auto add_to_tiles_list = [&](tog::TacticsTile* neighbor_tile) {
            neighbor_tile->m_path_finding_root_tile = current_tile;
            neighbor_tile->m_path_finding_distance = current_tile->m_path_finding_distance + 1;
            tactic_tile_process_queue.push_back(neighbor_tile);
        };

        for ( godot::Variant variant : current_tile->get_neighbors(height) ) {
            tog::TacticsTile* neighbor = godot::Object::cast_to<tog::TacticsTile>(variant);
            if ( !neighbor->m_path_finding_root_tile && (neighbor != tactics_root_tile) ) {
                //finish
            }

        }

    }

}

godot::Array tog::TacticsArenaService::get_pathfinding_tilestack(tog::TacticsTile* tactics_tile) {

}

tog::TacticsTile* tog::TacticsArenaService::get_nearest_target_adjacent_tile(tog::TacticsPawn* tactics_pawn, godot::Array target_tactics_pawns) {

}

tog::TacticsPawn* tog::TacticsArenaService::get_weakest_attackable_pawn(godot::Array tactics_pawns) {

}

void tog::TacticsArenaService::mark_hover_tile(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_tile) {

}

void tog::TacticsArenaService::mark_reachable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_tile, float distance) {

}

void tog::TacticsArenaService::mark_attackable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_tile, float distance) {

}
