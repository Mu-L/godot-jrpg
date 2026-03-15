#pragma once

#include "godot_cpp/classes/control.hpp"

namespace tog {

    class TacticsControl : public godot::Control {
        GDCLASS(TacticsControl, godot::Control);

    public:
        TacticsControl() = default;
        ~TacticsControl() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
