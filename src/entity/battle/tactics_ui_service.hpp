#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsUIService : public godot::Object {
        GDCLASS(TacticsUIService, godot::Object);

    public:
        TacticsUIService() = default;
        ~TacticsUIService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:

    };

}
