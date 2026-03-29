#pragma once

#include "input_capture.hpp"
#include "tactics_controls_service.hpp"

#include "resources/battle/tactics_arena_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/control.hpp"

namespace tog {

    class TacticsControlsService;

    //Handles UI elements and player controls for the Tactics systems
    class TacticsControls : public godot::Control {
        GDCLASS(TacticsControls, godot::Control);

    public:
        TacticsControls() = default;
        ~TacticsControls() override = default;

        //Initialize the service with necessary resources
        void _ready() override;
        //Handle physics-based processing
        //void _physics_process(double p_delta) override;
        //Handle input events
        //void _input(const godot::Ref<godot::InputEvent> &p_event) override;
        //Sets the cursor shape to 'move'
        void set_cursor_shape_to_move();
        /*
        //Sets the cursor shape to 'arrow'
        void set_cursor_shape_to_arrow();
        //Moves the camera based on input
        void move_camera(float delta);
        //Retrieves an action button node
        godot::Button* get_action(godot::String action = "");
        //Checks if the mouse is hovering over a UI element
        bool is_mouse_hovering_ui_elem();
        //Sets the visibility of the actions menu
        void set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn);
        //Gets the 3D position of the mouse in the game world
        godot::Object* get_3d_canvas_mouse_position(int collision_mask);
        //Selects a pawn for the player
        void select_pawn(tog::TacticsPlayer* tactics_player);
        //Initiates the process of selecting a new location for the pawn
        void select_new_location();
        //Initiates the process of selecting a pawn to attack
        void select_pawn_to_attack();
        //Handles the player's intention to move
        void player_wants_to_move();
        //Handles the player's intention to cancel an action
        void player_wants_to_cancel();
        //Handles the player's intention to wait
        void player_wants_to_wait();
        //Handles the player's intention to skip their turn
        void player_wants_to_skip_turn();
        //Handles the player's intention to attack
        void player_wants_to_attack();
        */

    protected:
        static void _bind_methods() {}

    public:
        //Resource containing control-related data and settings
        godot::Ref<tog::TacticsControlsResource> m_tactics_control_resource;
        //Resource containing camera-related data and settings
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource containing participant-related data and settings
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource containing arena-related data and settings
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;
        //Currently selected pawn
        tog::TacticsPawn* m_tactics_pawn = nullptr;
        //Service handling control logic
        godot::Ref<tog::TacticsControlsService> m_tactics_control_service;
        //Texture for Xbox controller layout
        godot::Ref<godot::Texture2D> m_layout_xbox_texture;
        //Texture for PC controls layout
        godot::Ref<godot::Texture2D> m_layout_pc_texture;
        tog::InputCapture* m_input_capture;

    };

}
