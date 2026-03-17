#pragma once

#include "godot_cpp/classes/static_body3d.hpp"

namespace tog {

    //Handles tiles, hover colors, tile state, pathfinding
    //This is ultimately a module, as it is programatically appended onto every tile by way of the TacticsTileService.
    class TacticsTile : public godot::StaticBody3D {
        GDCLASS(TacticsTile, godot::StaticBody3D);

    public:

        TacticsTile() = default;
        ~TacticsTile() override = default;

    protected:

        static void _bind_methods() {

        }

    private:



    };

}
