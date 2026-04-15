#pragma once
#include "tactics_arena_service.hpp"
#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    class TacticsArenaService;
    class TacticsTile;
    class TacticsPawn;
    class TacticsArenaResource;

    //Tile config & sorting, neighbours, hover & reach UI overlay, pathfinding and targeting utilities.
    //Resource Interface: [TacticsArenaResource] -- Service: [TacticsArenaService]
    //Dependency: [TacticsTile] -- Service: [TacticsTileService]
    class TacticsArena : public godot::Node3D {
        GDCLASS(TacticsArena, godot::Node3D);

    public:
        TacticsArena() = default;
        ~TacticsArena() override = default;

        void _ready() override;

        //Resets all tile markers in the arena
        void reset_all_tile_markers();

        //Configures all tiles in the arena
        void configure_tiles();

        //Processes tiles surrounding a given root tile
        //[param root_tile] The central tile to process around
        //[param height] The height to consider for processing
        //[param allies_on_map] Array of allied pawns on the map (optional)
        void process_surrounding_tiles(tog::TacticsTile* root_tile, float height, godot::Array allies_on_map = {});

        //Returns an array of tiles representing the pathfinding stack to a given tile
        //[param to] The destination tile
        //[returns] Array of tiles forming the path
        godot::Array get_pathfinding_tilestack(tog::TacticsTile* to);

        //Finds the nearest tile adjacent to any target pawn
        //[param pawn] The pawn seeking a target
        //[param target_pawns] Array of potential target pawns
        //[returns] The nearest adjacent tile to a target
        tog::TacticsTile* get_nearest_target_adjacent_tile(tog::TacticsPawn* tactics_pawn, godot::Array target_pawns);

        //Identifies the weakest attackable pawn from an array of pawns
        //[param pawn_arr] Array of pawns to evaluate
        //[returns] The weakest attackable pawn
        tog::TacticsPawn* get_weakest_attackable_pawn(godot::Array pawns);

        //Marks a tile as hovered
        //[param tile] The tile to mark as hovered
        void mark_hover_tile(tog::TacticsTile* tactics_tile);

        //Marks tiles reachable within a certain distance from a root tile
        //[param root] The starting tile
        //[param distance] The maximum distance to consider
        void mark_reachable_tiles(tog::TacticsTile* root_tile, float distance);

        //Marks tiles attackable within a certain distance from a root tile
        //[param root] The starting tile
        //[param distance] The maximum attack distance
        void mark_attackable_tiles(tog::TacticsTile* root_tile, float distance);
        
    protected:
        static void _bind_methods() {}

    private:
        //Resource containing arena-related data and configurations
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;
        //Service handling arena-related operations
        godot::Ref<tog::TacticsArenaService> m_tactics_arena_service;

    };

}
