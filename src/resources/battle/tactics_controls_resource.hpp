#pragma once

#include "util/bind.hpp"

#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/classes/resource.hpp"

namespace tog {

    class TacticsPawn;
    class TacticsPlayer;

    //Resource class for managing tactics controls and related signals
    class TacticsControlsResource : public godot::Resource {
        GDCLASS(TacticsControlsResource, godot::Resource);

    public:

        TacticsControlsResource();
        ~TacticsControlsResource() override = default;

        // getter/setter for property value
        void set_is_joystick(bool value) { m_is_joystick = value; }
        bool get_is_joystick() const     { return m_is_joystick; }
        // getter/setter for property value
        void set_input_hints_folded(bool value) { m_input_hints_folded = value; }
        bool get_input_hints_folded() const     { return m_input_hints_folded; }

        //Sets the visibility of the actions menu
        void set_actions_menu_visibility(bool visible, TacticsPawn* pawn);
        //Initiates camera movement
        void move_camera(float delta);
        //Selects a pawn for the given player
        void select_pawn(TacticsPlayer* player);
        //Selects a pawn to attack
        void select_pawn_to_attack();
        //Selects a new location
        void select_new_location();
        //Sets the cursor shape to "move"
        void set_cursor_shape_to_move();
        //Sets the cursor shape to "arrow"
        void set_cursor_shape_to_arrow();

    protected:
        static void _bind_methods();

    public:
        //property - indicates whether the current input device is a joystick
        bool m_is_joystick{false};
        //property - indicates whether the input hints are folded
        bool m_input_hints_folded{false};
        //dictionary of available actions and their corresponding methods
        godot::Dictionary m_actions;
    };

}

