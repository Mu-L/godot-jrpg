#pragma once

#include "tactics_pawn.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    //Service class for managing the HUD (Heads-Up Display) of a pawn in the tactics game
    class TacticsPawnHudService : public godot::RefCounted {
        GDCLASS(TacticsPawnHudService, godot::RefCounted);

    public:
        TacticsPawnHudService() = default;
        ~TacticsPawnHudService() override = default;

        //Updates the health display of the pawn's character UI
        //@param pawn: The TacticsPawn whose health display needs to be updated
        void update_character_health(const tog::TacticsPawn* tactics_pawn);

        //Applies a tint to the pawn's sprite when it's unable to act
        //@param pawn: The TacticsPawn to apply the tint to
        void tint_when_unable_to_act(tog::TacticsPawn* tactics_pawn);

    protected:
        static void _bind_methods() {}

    private:

    };

}
