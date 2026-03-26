#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsControlsInputService : public godot::Object {
        GDCLASS(TacticsControlsInputService, godot::Object);

    public:
        TacticsControlsInputService() = default;
        ~TacticsControlsInputService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
