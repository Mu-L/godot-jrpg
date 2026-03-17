#pragma once

#include "core/constants.hpp"
#include "entity/battle/tactics_pawn.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //possible actions that can happen
    enum class STAGE {
        //Constant for the pawn selection stage
        SELECT_PAWN = 0,
        //Constant for the action display stage
        SHOW_ACTION,
        //Constant for the movement display stage
        SHOW_MOVEMENTS,
        //Constant for the location selection stage
        SELECT_LOCATION,
        //Constant for the pawn movement stage
        MOVE_PAWN,
        //Constant for the target display stage
        DISPLAY_TARGETS,
        //Constant for the attack target selection stage
        SELECT_ATTACK_TARGET,
        //Constant for the attack execution stage
        ATTACK
    };

    //Attributes & signals of the tactics participant
    class TacticsParticipantResource : public godot::Resource {
        GDCLASS(TacticsParticipantResource, godot::Resource);

    public:

        TacticsParticipantResource() = default;
        ~TacticsParticipantResource() override = default;

        //Emits the skip_turn signal
        void skip_turn();

    protected:
        static void _bind_methods() {
            //Signal emitted when a turn is skipped
            rl::signal_binding<TacticsParticipantResource, tog::node::signal::TacticsParticipantResource::called_skip_turn>::add<>();
        }

    private:
        //The current stage of the participant's turn
        int m_stage = 0;
        //The currently active pawn
        tog::TacticsPawn* m_tactics_pawn = nullptr;
        //The pawn that can be attacked
        tog::TacticsPawn* m_attackable_pawn = nullptr;
        //The node containing the target pawns
        godot::Node* m_targets = nullptr;
        //Flag to control the display of opponent stats
        bool m_display_opponent_stats = false;
        //Flag indicating if the turn has just started
        bool m_turn_just_started = true;

    };

}

