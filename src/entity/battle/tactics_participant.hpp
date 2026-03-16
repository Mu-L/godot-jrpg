#pragma once

#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    class TacticsParticipant : public godot::Node3D {
        GDCLASS(TacticsParticipant, godot::Node3D);

    public:
        TacticsParticipant() = default;
        ~TacticsParticipant() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
