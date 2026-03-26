#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsControlsCameraService : public godot::Object {
        GDCLASS(TacticsControlsCameraService, godot::Object);

    public:
        TacticsControlsCameraService() = default;
        ~TacticsControlsCameraService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
