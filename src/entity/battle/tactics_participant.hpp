#pragma once

#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    class TacticsControlsResource;
    class TacticsParticipantResource;
    class TacticsCameraResource;
    class TacticsPlayer;
    class TacticsOpponent;
    class TacticsParticipantService;
    class TacticsArena;

    //Handles participant (i.e. Player & Opponent) actions and decision-making
    //Resource Interface: [TacticsParticipantResource] -- Service: [TacticsParticipantService]
    //Parent of: [TacticsPlayer], [TacticsOpponent]
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
        virtual bool is_pawn_configured() {
            return false;
        };

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
        void skip_turn();

    protected:
        static void _bind_methods() {
            godot::ClassDB::bind_method(godot::D_METHOD("skip_turn"), &TacticsParticipant::skip_turn);
        }

    public:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Service handling participant logic and operations
        godot::Ref<tog::TacticsParticipantService> m_tactics_participant_service;
        //Reference to the TacticsArena node
        tog::TacticsArena* m_tactics_arena = nullptr;
        //Reference to the TacticsPlayer node
        tog::TacticsPlayer* m_tactics_player = nullptr;
        //Reference to the TacticsOpponent node
        tog::TacticsOpponent* m_tactics_opponent = nullptr;

    };

}
