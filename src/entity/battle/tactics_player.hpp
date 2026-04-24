#pragma once

#include "tactics_participant.hpp"
#include "singletons/console.hpp"

namespace tog {

    class TacticsParticipant;
    class TacticsPlayerService;


    //Handles player-specific actions and logic in the tactics game
    //Extends TacticsParticipant to provide player-specific functionality
    //Service: [TacticsPlayerService]
    class TacticsPlayer : public TacticsParticipant {
        GDCLASS(TacticsPlayer, TacticsParticipant);

    public:
        TacticsPlayer() = default;
        ~TacticsPlayer() override = default;

        //Initializes the TacticsPlayer node
        void _ready() override;

        //Processes player-related physics updates
        //@param _delta: Time elapsed since the last frame (unused)
        void _physics_process(double p_delta) override;

        //Checks if the player's pawn is properly configured
        //@return: Whether the player's pawn is configured
        bool is_pawn_configured() override;

        //Displays the available actions for the player's pawn
        void show_avaliable_pawn_actions();

        //Displays the available movement options for the player's pawn
        void show_avaliable_movements();

        //Displays the attackable targets for the player's pawn
        void display_attackable_targets();

        //Initiates the movement of the player's pawn
        void move_pawn();


    protected:
        static void _bind_methods() {}

    private:
        rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
        //Service handling player-specific logic and operations
        godot::Ref<tog::TacticsPlayerService> m_tactics_player_service;
    };

}
