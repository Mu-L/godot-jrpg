#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsControlsSelectionService : public godot::Object {
        GDCLASS(TacticsControlsSelectionService, godot::Object);

    public:
        TacticsControlsSelectionService() = default;
        ~TacticsControlsSelectionService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
