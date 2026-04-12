#pragma once

#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    //Handles participant (i.e. Player & Opponent) actions and decision-making
    //Resource Interface: [TacticsParticipantResource] -- Service: [TacticsParticipantService]
    //Parent of: [TacticsPlayer], [TacticsOpponent]

    class TacticsControlsResource;
    class TacticsParticipantResource;
    class TacticsCameraResource;
    class TacticsPlayer;
    class TacticsOpponent;
    class TacticsParticipantService;

    class TacticsParticipant : public godot::Node3D {
        GDCLASS(TacticsParticipant, godot::Node3D);

    public:
        TacticsParticipant() = default;
        ~TacticsParticipant() override = default;

        //initalize sub services
        void _ready() override;

        //Performs the participant's action
        //@param delta: Time elapsed since the last frame
        //@param is_player: Whether the acting participant is the player
        //@param parent: The parent node of the participant
        void act(float delta, bool is_player, godot::Node3D* parent);

        //Configures the participant with camera and control resources
        //@param my_camera: The camera resource to use
        //@param my_control: The control resource to use
        void configure(
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource
        );

        //todo: the "is_configrued" function should be virtual because it will be used by TacticsPlayer and TacticsOpponent

    protected:
        static void _bind_methods() {}

    protected:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Service handling participant logic and operations
        godot::Ref<tog::TacticsParticipantService> m_tactics_participant_service;
        //Reference to the TacticsArena node
        godot::Node3D* m_tactics_arena = nullptr;
        //Reference to the TacticsPlayer node
        tog::TacticsPlayer* m_tactics_player = nullptr;
        //Reference to the TacticsOpponent node
        tog::TacticsOpponent* m_tactics_opponent = nullptr;

    };

}
