#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawnMovementService : public godot::RefCounted {
        GDCLASS(TacticsPawnMovementService, godot::RefCounted);

    public:
        TacticsPawnMovementService() = default;
        ~TacticsPawnMovementService() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}

