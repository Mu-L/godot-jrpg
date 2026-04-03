#pragma once

#include "tactics_pawn.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawn;

    //Service class for managing animations of pawns in the tactics game
    class TacticsPawnAnimationService : public godot::RefCounted {
        GDCLASS(TacticsPawnAnimationService, godot::RefCounted);

    public:
        TacticsPawnAnimationService() = default;
        ~TacticsPawnAnimationService() override = default;

        //Sets up the pawn's character animations
        //@param pawn: The TacticsPawn to set up animations for
        void setup(const tog::TacticsPawn* tactics_pawn);
        //Starts the appropriate animation for the pawn based on its current state
        //@param pawn: The TacticsPawn to animate
        void start_animator(const tog::TacticsPawn* tactics_pawn);

    protected:
        static void _bind_methods() {}

    private:

    };

}



