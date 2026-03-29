#pragma once

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsControlsService : public godot::RefCounted {
        GDCLASS(TacticsControlsService, godot::RefCounted);

    public:
        TacticsControlsService() = default;
        ~TacticsControlsService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
