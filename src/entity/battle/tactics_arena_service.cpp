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

        for ( const godot::Variant& variant : current_tile->get_neighbors(height) ) {
            tog::TacticsTile* neighbor = godot::Object::cast_to<tog::TacticsTile>(variant);
            if ( !neighbor->m_path_finding_root_tile && (neighbor != tactics_root_tile) ) {
                if (!neighbor->is_taken()) {
                    add_to_tiles_list(neighbor);
                } else if (allies_on_map.size() > 0) {
                    if (allies_on_map.has(neighbor)) {
                        add_to_tiles_list(neighbor);
                    }
                }
            }
        }
    }
}

godot::Array tog::TacticsArenaService::get_pathfinding_tilestack(tog::TacticsTile* tactics_tile) {
    godot::Array path_tiles_stack;

    while (tactics_tile) {
        tactics_tile->m_hover = true;
        path_tiles_stack.push_front(tactics_tile->get_global_position());
        tactics_tile = tactics_tile->m_path_finding_root_tile;
    }

    m_tactics_arena_resource->m_path_tiles_stack = path_tiles_stack;

    return path_tiles_stack;
}

tog::TacticsTile* tog::TacticsArenaService::get_nearest_target_adjacent_tile(tog::TacticsPawn* tactics_pawn, godot::Array target_tactics_pawns) {
    tog::TacticsTile* nearest_target = nullptr;

    for ( const godot::Variant& pawn_variant : target_tactics_pawns ) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(pawn_variant);
        if ( pawn->m_stats_node->m_current_health <= 0 ) continue;

        for ( const godot::Variant& tile_variant : pawn->get_tile()->get_neighbors(tactics_pawn->m_stats_node->m_jump) ) {
            auto* tile = godot::Object::cast_to<tog::TacticsTile>(tile_variant);
            if ( !nearest_target || (tile->m_path_finding_distance < nearest_target->m_path_finding_distance) ) {
                if ( tile->m_path_finding_distance > 0 && !tile->is_taken() ) {
                    nearest_target = tile;
                }
            }
        }
    }

    while (nearest_target && !nearest_target->m_reachable) {
        nearest_target = nearest_target->m_path_finding_root_tile;
    }

    return (nearest_target) ? nearest_target : tactics_pawn->get_tile();
}

tog::TacticsPawn* tog::TacticsArenaService::get_weakest_attackable_pawn(godot::Array tactics_pawns) {
    tog::TacticsPawn* weakest_pawn = nullptr;

    for ( const godot::Variant& variant : tactics_pawns ) {
        auto* pawn = godot::Object::cast_to<tog::TacticsPawn>(variant);
        if ( !weakest_pawn || (pawn->m_stats_node->m_current_health < weakest_pawn->m_stats_node->m_current_health) ) {
            if ( pawn->m_stats_node->m_current_health > 0  && pawn->get_tile()->m_attackable ) {
                weakest_pawn = pawn;
            }
        }
    }
    return weakest_pawn;
}

void tog::TacticsArenaService::mark_hover_tile(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_tile) {
    for ( const godot::Variant& variant : tactics_arena->get_node<godot::Node3D>(tog::node::name::BattleTest::Tiles)->get_children() ) {
        auto* tile = godot::Object::cast_to<tog::TacticsTile>(variant);
        tile->m_hover = false;
    }
    if (tactics_tile) {
        tactics_tile->m_hover = true;
    }
}

void tog::TacticsArenaService::mark_reachable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_root_tile, float distance) {
    for ( const godot::Variant& variant : tactics_arena->get_node<godot::Node3D>(tog::node::name::BattleTest::Tiles)->get_children() ) {
        auto* tile = godot::Object::cast_to<tog::TacticsTile>(variant);

        bool has_distance = (tile->m_path_finding_distance > 0);
        bool reachable = (tile->m_path_finding_distance <= distance);
        bool not_taken = !tile->is_taken();
        bool is_root = (tile == tactics_root_tile);

        tile->m_reachable = (has_distance && reachable && not_taken) or is_root;
    }
}

void tog::TacticsArenaService::mark_attackable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_root_tile, float distance) {
    for ( const godot::Variant& variant : tactics_arena->get_node<godot::Node3D>(tog::node::name::BattleTest::Tiles)->get_children() ) {
        auto* tile = godot::Object::cast_to<tog::TacticsTile>(variant);

        bool has_distance = (tile->m_path_finding_distance > 0);
        bool reachable = (tile->m_path_finding_distance <= distance);;
        bool is_root = (tile == tactics_root_tile);

        tile->m_reachable = (has_distance && reachable) or is_root;
    }
}
