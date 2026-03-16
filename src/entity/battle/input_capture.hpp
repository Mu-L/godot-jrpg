#pragma once

#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    class InputCapture : public godot::Node3D {
        GDCLASS(InputCapture, godot::Node3D);

    public:

        InputCapture() = default;
        ~InputCapture() override = default;

    protected:

        static void _bind_methods() {

        }

    private:



    };

}
