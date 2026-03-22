#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsCameraPanningService : public godot::Object {
        GDCLASS(TacticsCameraPanningService, godot::Object);

    public:
        TacticsCameraPanningService() = default;
        ~TacticsCameraPanningService() override = default;

    protected:
        void static _bind_methods() {

        }

    private:
    };

}

