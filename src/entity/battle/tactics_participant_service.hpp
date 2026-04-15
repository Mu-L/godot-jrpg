#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsParticipant;
    class TacticsCameraResource;
    class TacticsParticipantResource;
    class TacticsControlsResource;
    class TacticsParticipantTurnService;
    class TacticsParticipantCombatService;
    class TacticsPlayer;

    //Service class for TacticsParticipant
    //Dependency of: [TacticsParticipant]
    class TacticsParticipantService : public godot::RefCounted {
        GDCLASS(TacticsParticipantService, godot::RefCounted);

    public:
        TacticsParticipantService() = default;
        TacticsParticipantService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource);
        ~TacticsParticipantService() override = default;

        //Sets up the TacticsParticipantService
        //@param _participant: The TacticsParticipant node to set up
        void setup(tog::TacticsParticipant* tactics_participant);

        //Handles the participant's action
        //@param delta: Time elapsed since the last frame
        //@param is_player: Whether the acting participant is the player
        //@param parent: The parent node of the participant
        //@param participant: The TacticsParticipant node
        void act(float delta, bool is_player, godot::Node3D* parent, tog::TacticsParticipant* tactics_participant);

        //Configures the service with camera and control resources
        //@param my_camera: The camera resource to use
        //@param my_control: The control resource to use
        void configure(
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource
        );

        //Checks if the participant is properly configured
        //@param parent: The parent node of the participant
        //@return: Whether the participant is configured
        bool is_configured(godot::Node3D* parent);

        //Checks if the participant can perform an action
        //@param parent: The parent node of the participant
        //@return: Whether the participant can act
        bool can_act(godot::Node3D* parent);

        //Resets the participant's turn
        //@param parent: The parent node of the participant
        void reset_turn(godot::Node3D* parent);

        //Skips the participant's turn
        //@param player: The TacticsPlayer node
        void skip_turn(tog::TacticsPlayer* tactics_player);

    protected:
        static void _bind_methods() {}

    public:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Service handling turn-related logic
        godot::Ref<tog::TacticsParticipantTurnService> m_tactics_participant_turn_service;
        //Service handling combat-related logic
        godot::Ref<tog::TacticsParticipantCombatService> m_tactics_combat_service;
    };

}
