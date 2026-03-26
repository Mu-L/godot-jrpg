#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsControlsService : public godot::Object {
        GDCLASS(TacticsControlsService, godot::Object);

    public:
        TacticsControlsService() = default;
        ~TacticsControlsService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
