#pragma once

#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsOpponent;
    class TacticsArena;

    //Service class for TacticsOpponent
    class TacticsOpponentService : public godot::RefCounted {
        GDCLASS(TacticsOpponentService, godot::RefCounted);

    public:
        TacticsOpponentService() = default;
        TacticsOpponentService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource,
            tog::TacticsArena* arena
            ) : m_tactics_participant_resource{participant_resource},
                m_tactics_camera_resource{camera_resource},
                m_tactics_controls_resource{controls_resource},
                m_tactics_arena{arena} {};
        ~TacticsOpponentService() override = default;

        //Checks if all opponent pawns are properly configured
        //@param opponent: The TacticsOpponent node to check
        //@return: Whether all pawns are configured
        bool is_pawn_configured(tog::TacticsOpponent* tactics_opponent);

        //Selects a pawn for the opponent to control
        //@param opponent: The TacticsOpponent node
        void choose_pawn(tog::TacticsOpponent* tactics_opponent);

        //Initiates the opponent's pawn to chase the nearest enemy
        //@param opponent: The TacticsOpponent node
        //@param player_node: The player's node
        void chase_nearest_enemy(tog::TacticsOpponent* tactics_opponent, godot::Node* player_node);

        //Checks if the opponent's pawn has finished moving
        void is_pawn_done_moving();

        //Selects a pawn for the opponent to attack
        void choose_pawn_to_attack();

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Reference to the TacticsArena node
        tog::TacticsArena* m_tactics_arena = nullptr;
    };

}