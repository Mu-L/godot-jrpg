#pragma once

#include "tactics_controls_camera_service.hpp"
#include "tactics_controls_input_service.hpp"
#include "tactics_controls_selection_service.hpp"
#include "tactics_ui_service.hpp"
#include "resources/battle/tactics_arena_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsControlsInputService;
    class TacticsControlsSelectionService;
    class TacticsUIService;

    //Service class for managing tactics controls and related functionalities
    class TacticsControlsService : public godot::RefCounted {
        GDCLASS(TacticsControlsService, godot::RefCounted);

    public:
        TacticsControlsService() = default;
        TacticsControlsService(const godot::Ref<tog::TacticsControlsResource>& tactics_controls_resource,
                               const godot::Ref<tog::TacticsCameraResource>& tactics_camera_resource,
                               const godot::Ref<tog::TacticsParticipantResource>& tactics_participant_resource,
                               const godot::Ref<tog::TacticsArenaResource>& tactics_arena_resource,
                               godot::Node* input_capture);
        ~TacticsControlsService() override = default;

        //Sets up signal connections and performs initial checks
        void setup(tog::TacticsControls* tactics_controls);

        //Performs physics processing tasks
        void physics_process(float delta, tog::TacticsControls* tactics_controls);

        //Handles input events
        void handle_input(const godot::Ref<godot::InputEvent>& event);

        //Delegates setting actions menu visibility to the UI service
        void set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn, tog::TacticsControls* tactics_controls);

        //Delegates pawn selection to the pawn selection service
        void select_pawn(tog::TacticsPlayer* tactics_player, tog::TacticsControls* tactics_controls);

        //Delegates new location selection to the pawn selection service
        void select_new_location(tog::TacticsControls* tactics_controls);

        //Delegates pawn attack selection to the pawn selection service
        void select_pawn_to_attack(tog::TacticsControls* tactics_controls);

        //Handles player's move action
        void player_wants_to_move();

        //Handles player's cancel action
        void player_wants_to_cancel();

        //Handles player's wait action
        void player_wants_to_wait();

        //Handles player's skip turn action
        void player_wants_to_skip_turn();

        //Handles player's attack action
        void player_wants_to_attack();

    protected:
        static void _bind_methods() {}

    private:
        //Reference to the TacticsControlsResource
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;

        //Reference to the TacticsCameraResource
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;

        //Reference to the TacticsParticipantResource
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;

        //Reference to the TacticsArenaResource
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;

        //Node for capturing mouse clicks
        godot::Node* m_input_capture;

        //Service for handling input-related operations
        godot::Ref<tog::TacticsControlsInputService> m_tactics_controls_input_service;

        //Service for managing UI-related operations.
        godot::Ref<tog::TacticsUIService> m_tactics_ui_service;

        //Service for handling camera-related operations.
        godot::Ref<tog::TacticsControlsCameraService> m_tactics_controls_camera_service;

        //Service for managing pawn selection operations
        godot::Ref<tog::TacticsControlsSelectionService> m_tactics_controls_selection_service;
    };

}
