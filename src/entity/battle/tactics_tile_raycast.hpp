#pragma once

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

        godot::Array get_all_neighbors(float height);
        godot::Ref<godot::Object> get_object_above();

    protected:
        static void _bind_methods() {}
    };

}


