#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"

namespace tog {

    class TacticsCameraService : public godot::RefCounted {
        GDCLASS(TacticsCameraService, godot::RefCounted);

    public:
        TacticsCameraService() = default;
        ~TacticsCameraService() override = default;

    protected:
        void static _bind_methods() {

        }

    private:


    };

}

