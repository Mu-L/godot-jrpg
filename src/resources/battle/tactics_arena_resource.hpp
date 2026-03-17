#pragma once

#include "core/constants.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //Attributes, controller & signals of the tactics arena
    class TacticsArenaResource : public godot::Resource {
        GDCLASS(TacticsArenaResource, godot::Resource);

    public:

        TacticsArenaResource() = default;
        ~TacticsArenaResource() override = default;


        // Triggers the reset of all tile markers
        void reset_all_tile_markers();

        //Requests the pathfinding tilestack for a given tile
        //[param tile] The target tile for pathfinding
        //[returns] The array of tiles in the pathfinding stack
        //godot::Array get_pathfinding_tilestack(tog::TacticsTile tile);

        //Marks a tile as hovered
        //[param tile] The tile to be marked as hovered
        //void mark_hover_tile(tog::TacticsTile tile);


    protected:
        static void _bind_methods() {
            //Emitted when all tile markers need to be reset
            rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_reset_all_tile_markers>::add<>();
            //Emitted when pathfinding tilestack is requested - The target tile for pathfinding
            rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_get_pathfinding_tilestack>::add<godot::Object*>();
            //Emitted when a tile needs to be marked as hovered -  The tile to be marked as hovered
            rl::signal_binding<TacticsArenaResource, tog::node::signal::TacticsArenaResource::called_mark_hover_tile>::add<godot::Object*>();
        }

    private:
        godot::Array m_path_tiles_stack;

    };

}

