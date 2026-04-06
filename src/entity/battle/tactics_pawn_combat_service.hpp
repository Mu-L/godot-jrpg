#pragma once

#include "tactics_pawn.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    //Service class for managing combat actions of pawns in the tactics game
    class TacticsPawnCombatService : public godot::RefCounted {
        GDCLASS(TacticsPawnCombatService, godot::RefCounted);

    public:
        TacticsPawnCombatService() = default;
        ~TacticsPawnCombatService() override = default;

        //Executes an attack from one pawn to another
        //@param pawn: The attacking TacticsPawn
        //@param target_pawn: The TacticsPawn being attacked
        //@param delta: Time elapsed since the last frame
        //@return: Whether the attack was completed
        bool attack_target_pawn(tog::TacticsPawn* tactics_pawn, tog::TacticsPawn* target_tactics_pawn, float delta);

    protected:
        static void _bind_methods() {}

    private:

    };

}


