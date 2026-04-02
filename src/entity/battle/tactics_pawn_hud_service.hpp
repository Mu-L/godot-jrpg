#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawnHudService : public godot::RefCounted {
        GDCLASS(TacticsPawnHudService, godot::RefCounted);

    public:
        TacticsPawnHudService() = default;
        ~TacticsPawnHudService() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}
