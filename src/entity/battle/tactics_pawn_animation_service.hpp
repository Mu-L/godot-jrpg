#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawnAnimationService : public godot::RefCounted {
        GDCLASS(TacticsPawnAnimationService, godot::RefCounted);

    public:
        TacticsPawnAnimationService() = default;
        ~TacticsPawnAnimationService() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}



