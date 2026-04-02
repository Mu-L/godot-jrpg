#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawnCombatService : public godot::RefCounted {
        GDCLASS(TacticsPawnCombatService, godot::RefCounted);

    public:
        TacticsPawnCombatService() = default;
        ~TacticsPawnCombatService() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}


