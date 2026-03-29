#pragma once

#include "tactics_controls_input_service.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "resources/battle/tactics_arena_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"


namespace tog {

    //Service class for managing pawn and tile selection in the Tactics game.
    class TacticsControlsSelectionService : public godot::RefCounted {
        GDCLASS(TacticsControlsSelectionService, godot::RefCounted);

    public:
        TacticsControlsSelectionService() = default;
        //Initializes the TacticsControlsSelectionService with necessary resources and services
        TacticsControlsSelectionService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsArenaResource>& arena_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsInputService>& controls_input_service);
        ~TacticsControlsSelectionService() override = default;

        //Handles the selection of a pawn
        void select_pawn(tog::TacticsPlayer* tactics_player, tog::TacticsControls* tactics_controls);
        //Selects the pawn currently hovered by the mouse
        godot::PhysicsBody3D select_hovered_pawn(tog::TacticsControls* tactics_controls);
        //Handles the selection of a new location for the current pawn
        void select_new_location(tog::TacticsControls* tactics_controls);
        //Handles the selection of a pawn to attack
        void select_pawn_to_attack(tog::TacticsControls* tactics_controls);
        //Handles the player's intention to move
        void player_wants_to_move();
        //Handles the player's intention to cancel
        void player_wants_to_cancel();
        //Handles the player's intention to wait
        void player_wants_to_wait();
        //Handles the player's intention to skip turn
        void player_wants_to_skip_turn();
        //Handles the player's intention to attack
        void player_wants_to_attack();


    protected:
        static void _bind_methods() {}

    private:
        //Reference to the TacticsParticipantResource
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Reference to the TacticsArenaResource
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;
        //Reference to the TacticsControlsResource
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Reference to the TacticsCameraResource
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Reference to the TacticsControlsInputService
        godot::Ref<tog::TacticsControlsInputService> m_tactics_controls_input_service;

    };

}
