#pragma once

#include "tactics_opponent_service.hpp"
#include "tactics_participant.hpp"

namespace tog {

    class TacticsParticipant;

    //Handles opponent AI actions and decision-making
    class TacticsOpponent : public TacticsParticipant {
        GDCLASS(TacticsOpponent, TacticsParticipant);

    public:
        TacticsOpponent() = default;
        ~TacticsOpponent() override = default;

        //Initializes the TacticsOpponent node
        void _ready() override;

        //Checks if the opponent's pawn is properly configured
        //@return: Whether the pawn is configured
        bool is_pawn_configured();

        //Chooses a pawn for the opponent to act with
        void choose_pawn();

        //Initiates the action of chasing the nearest enemy
        void chase_nearest_enemy();

        //Checks if the opponent's pawn has finished moving
        void is_pawn_done_moving();

        //Chooses a pawn for the opponent to attack
        void choose_pawn_to_attack();

    protected:
        static void _bind_methods() {}

    private:
        //Service handling opponent-specific logic and operations
        godot::Ref<tog::TacticsOpponentService> m_tactics_opponent_service;


    };

}
