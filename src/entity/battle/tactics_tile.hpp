#pragma once

#include "tactics_tile_raycast.hpp"

#include "util/utility.hpp"
#include "util/scene.hpp"

#include "godot_cpp/classes/static_body3d.hpp"
#include "godot_cpp/classes/standard_material3d.hpp"

namespace tog {

    //Handles tiles, hover colors, tile state, pathfinding
    //This is ultimately a module, as it is programatically appended onto every tile by way of the TacticsTileService.
    //Dependencies: [TacticsTileService] [br]
    //Used by: [TacticsArena]
    class TacticsTile : public godot::StaticBody3D {
        GDCLASS(TacticsTile, godot::StaticBody3D);

    public:

        TacticsTile();
        ~TacticsTile() override = default;

        void _process(double p_delta) override;

        //Returns all 4 directly adjacent tiles
        godot::TypedArray<godot::Node3D> get_neighbors(float height);
        //Returns any collider directly (<=1m) above
        godot::Object* get_tile_occupier();
        //Return whether target tile is occupied
        bool is_taken();
        //Resets the tile's markers (pf_root, pf_distance, reachable, attackable)
        void reset_markers();
        //Initializes tile (disable hover, instantiate raycast & reset state)
        void configure_tile();

    protected:

        static void _bind_methods() {}

    private:
        //Resource for tile raycasting
        rl::resource::preload::packed_scene<tog::TacticsTileRaycast> m_tactics_tile_raycast_scene{tog::path::resource::battle::tactics_tile_raycast};
        //Whether the tile is reachable
        bool m_reachable = false;
        //Whether the tile is attackable
        bool m_attackable = false;
        //Whether the tile is being hovered over
        bool m_hover = false;
        //Pathfinding starting point - used by [TacticsArena]
        tog::TacticsTile* m_path_finding_root_tile{};
        //The distance to cover. Used by [TacticsArena]
        float m_path_finding_distance{};
        //Material for hover state
        godot::Ref<godot::StandardMaterial3D> m_hover_material{};
        //Material for reachable state
        godot::Ref<godot::StandardMaterial3D> m_reachable_material{};
        //Material for hover and reachable state
        godot::Ref<godot::StandardMaterial3D> m_hover_reachable_material{};
        //Material for attackable state
        godot::Ref<godot::StandardMaterial3D> m_attackable_material{};
        //Material for hover and attackable state
        godot::Ref<godot::StandardMaterial3D> m_hover_attackable_material{};

    };

}
