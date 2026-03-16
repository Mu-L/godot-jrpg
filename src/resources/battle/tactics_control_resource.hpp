#pragma once

#include "core/constants.hpp"
#include "entity/battle/tactics_pawn.hpp"
#include "entity/battle/tactics_player.hpp"
#include "util/bind.hpp"

#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //Resource class for managing tactics controls and related signals
    class TacticsControlResource : public godot::Resource {
        GDCLASS(TacticsControlResource, godot::Resource);

    public:

        TacticsControlResource();
        ~TacticsControlResource() override = default;

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
        static void _bind_methods() {
            //bind property to editor
            rl::bind_property(TacticsControlResource, is_joystick, bool);
            rl::bind_property(TacticsControlResource, input_hints_folded, bool);

            //Signal emitted when the actions menu visibility needs to be set
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_set_actions_menu_visibility>::add<bool, tog::TacticsPawn*>();
            //Signal emitted when the camera needs to be moved.
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_move_camera>::add<float>();
            //Signal emitted when a pawn needs to be selected
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_select_pawn>::add<tog::TacticsPlayer*>();
            //Signal emitted when a pawn needs to be selected for attack
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_select_pawn_to_attack>::add<>();
            //Signal emitted when a new location needs to be selected
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_select_new_location>::add<>();
            //Signal emitted when the cursor shape needs to be set to "move"
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_move>::add<>();
            //Signal emitted when the cursor shape needs to be set to "arrow"
            rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_set_cursor_shape_to_arrow>::add<>();
        }

    private:
        //property - indicates whether the current input device is a joystick
        bool m_is_joystick{false};
        //property - indicates whether the input hints are folded
        bool m_input_hints_folded{false};
        //dictionary of available actions and their corresponding methods
        godot::Dictionary m_actions;
    };

}

