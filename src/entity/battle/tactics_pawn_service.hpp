#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    //Service class for managing UI-related functionalities in the Tactics game
    class TacticsPawnService : public godot::RefCounted {
        GDCLASS(TacticsPawnService, godot::RefCounted);

    public:
        TacticsPawnService() = default;
        ~TacticsPawnService() override = default;

    protected:
        static void _bind_methods() {}

    private:
        //Service for handling pawn movement

    };

}
