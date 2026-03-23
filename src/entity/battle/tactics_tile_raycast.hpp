#pragma once

#include "core/assert.hpp"
#include "core/constants.hpp"

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/object.hpp"

namespace tog {

    //has a sub 3dnode "Neighbors"

    //Handles raycasting operations for TacticsTile
    //This class is responsible for detecting neighboring tiles and objects above the tile.
    //It is typically instantiated as a child of TacticsTile
    class TacticsTileRaycast : public godot::Node3D {
        GDCLASS(TacticsTileRaycast, godot::Node3D);

    public:

        TacticsTileRaycast() = default;
        ~TacticsTileRaycast() override = default;

        //Returns all the neighboring tiles within a given height range.
        //[param height] The maximum height difference to consider for neighbors.
        //[returns] An array of neighboring Node3D objects (typically TacticsTiles).
        godot::TypedArray<godot::Node3D> get_all_neighbors(float height);

        //Returns the object directly above the tile.
        //[returns] The object above the tile, or null if none found.
        godot::Object* get_object_above();

    protected:
        static void _bind_methods() {}
    };

}


