#pragma once

#include "tactics_arena.hpp"
#include "tactics_player.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPlayerService : public godot::RefCounted {
        GDCLASS(TacticsPlayerService, godot::RefCounted);

    public:
        TacticsPlayerService() = default;
        TacticsPlayerService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource,
            tog::TacticsArena* arena
        ) : m_tactics_participant_resource{participant_resource},
            m_tactics_camera_resource{camera_resource},
            m_tactics_controls_resource{controls_resource},
            m_tactics_arena{arena} {};
        ~TacticsPlayerService() override = default;

        //Toggles the display of enemy pawn stats
        //@param opponent_node: The opponent's node containing enemy pawns
        void toggle_enemy_stats(godot::Node* opponent_node);

        //## Checks if all player pawns are properly configured
        //## @param player: The TacticsPlayer node to check
        //## @return: Whether all pawns are configured
        bool is_pawn_configured(tog::TacticsPlayer* player);

        //Displays available actions for the current pawn
        void show_available_pawn_actions();

        //Displays available movement options for the current pawn
        void show_available_movements();

        //Displays attackable targets for the current pawn
        void display_attackable_pawns();

        //Initiates the movement of the current pawn
        void move_pawn();

    protected:
        static void _bind_methods() {}

    private:
        rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Reference to the TacticsArena node
        tog::TacticsArena* m_tactics_arena;

    };

}
