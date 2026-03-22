#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsCameraRotationService : public godot::Object {
        GDCLASS(TacticsCameraRotationService, godot::Object);

    public:
        TacticsCameraRotationService() = default;
        ~TacticsCameraRotationService() override = default;

    protected:
        void static _bind_methods() {

        }

    private:
    };

}

