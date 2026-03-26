#pragma once

#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //Attributes, controller & signals of the tactics arena
    class TacticsControlsResource : public godot::Resource {
        GDCLASS(TacticsControlsResource, godot::Resource);

    public:

        TacticsControlsResource() = default;
        ~TacticsControlsResource() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}

