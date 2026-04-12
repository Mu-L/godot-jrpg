#pragma once

#include "tactics_arena.hpp"
#include "tactics_pawn.hpp"
#include "resources/battle/tactics_arena_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsTile;
    class TacticsPawn;
    class TacticsArena;

    //Service class for TacticsArena
    class TacticsArenaService : public godot::RefCounted {
        GDCLASS(TacticsArenaService, godot::RefCounted);

    public:
        TacticsArenaService() = default;
        explicit TacticsArenaService(const godot::Ref<tog::TacticsArenaResource>& arena_resource) : m_tactics_arena_resource{arena_resource} {};
        ~TacticsArenaService() override = default;

        //Set up the arena by connecting signals
        //[param arena] The TacticsArena to set up
        void setup(tog::TacticsArena* tactics_arena);

        //Reset markers for all tiles in the arena
        //[param arena] The TacticsArena containing the tiles
        void reset_all_tile_markers(tog::TacticsArena* tactics_arena);

        //Configure tiles in the arena
        //[param arena] The TacticsArena to configure
        void configure_tiles(tog::TacticsArena* tactics_arena);

        //Process tiles surrounding a root tile
        //[param root_tile] The starting tile
        //[param height] The height to consider for neighbors
        //[param allies_on_map] Array of allied pawns on the map
        void process_surrounding_tiles(tog::TacticsTile* tactics_root_tile, float height, godot::Array allies_on_map = {});

        //Get the pathfinding tilestack to a target tile
        //[param to] The target tile
        //[returns] Array of global positions forming the path
        godot::Array get_pathfinding_tilestack(tog::TacticsTile* tactics_tile);

        //## Get the nearest tile adjacent to a target pawn
        //## [param pawn] The pawn seeking a target
        //## [param target_pawns] Array of potential target pawns
        //## [returns] The nearest adjacent tile or the pawn's current tile if no target found
        tog::TacticsTile* get_nearest_target_adjacent_tile(tog::TacticsPawn* tactics_pawn, godot::Array target_tactics_pawns);

        //## Get the weakest attackable pawn from an array of pawns
        //## [param pawn_arr] Array of pawns to evaluate
        //## [returns] The weakest attackable pawn or null if none found
        tog::TacticsPawn* get_weakest_attackable_pawn(godot::Array tactics_pawns);

        //## Mark a tile as hovered and unmark others
        //## [param arena] The TacticsArena containing the tiles
        //## [param tile] The tile to mark as hovered
        void mark_hover_tile(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_tile);

        //## Mark reachable tiles within a certain distance from a root tile
        //## [param arena] The TacticsArena containing the tiles
        //## [param root] The starting tile
        //## [param distance] The maximum distance to consider
        void mark_reachable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_root_tile, float distance);

        //## Mark attackable tiles within a certain distance from a root tile
        //## [param arena] The TacticsArena containing the tiles
        //## [param root] The starting tile
        //## [param distance] The maximum attack distance
        void mark_attackable_tiles(tog::TacticsArena* tactics_arena, tog::TacticsTile* tactics_root_tile, float distance);


    protected:
        static void _bind_methods() {}

    private:
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;

    };

}

