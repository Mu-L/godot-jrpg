#pragma once

#include "tactics_debug.hpp"

#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsParticipant;
    class TacticsPlayer;
    class TacticsOpponent;

    //Service class for handling turn-related actions
    //Parent: [TacticsParticipantService]
    class TacticsParticipantTurnService : public godot::RefCounted {
        GDCLASS(TacticsParticipantTurnService, godot::RefCounted);

    public:
        TacticsParticipantTurnService() = default;
        TacticsParticipantTurnService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource
            ) : m_tactics_participant_resource{participant_resource},
                m_tactics_camera_resource{camera_resource},
                m_tactics_controls_resource{controls_resource} {};
        ~TacticsParticipantTurnService() override = default;

        //Handles the player's turn
        //@param delta: Time elapsed since the last frame
        //@param player: The TacticsPlayer node
        //@param participant: The TacticsParticipant node
        void handle_player_turn(float delta, tog::TacticsPlayer* tactics_player, tog::TacticsParticipant* tactics_participant);

        //Handles the opponent's turn
        //@param delta: Time elapsed since the last frame
        //@param opponent: The TacticsOpponent node
        //@param participant: The TacticsParticipant node
        void handle_opponent_turn(float delta, tog::TacticsOpponent* tactics_opponent, tog::TacticsParticipant* tactics_participant);

        //Checks if the participant can perform an action
        //@param parent: The parent node of the participant
        //@return: Whether the participant can act
        bool can_act(godot::Node3D* parent);

        //Resets the participant's turn
        //@param parent: The parent node of the participant
        void reset_turn(godot::Node3D* parent);

        //Skips the participant's turn
        //@param player: The TacticsPlayer node
        void skip_turn(tog::TacticsPlayer* player);

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //logger
        //tog::debug::Logger* m_logger =
    };

}

