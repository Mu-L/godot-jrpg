#pragma once

#include "core/constants.hpp"
#include "util/bind.hpp"
#include "godot_cpp/classes/resource.hpp"


namespace tog {

    //Resource class for managing pawn data and state in the tactics game
    class TacticsPawnResource : public godot::Resource {
        GDCLASS(TacticsPawnResource, godot::Resource)
    public:
        TacticsPawnResource() = default;
        ~TacticsPawnResource() override = default;

    public:

        //Resets the pawn's turn, allowing it to move and attack again
        void reset_turn();
        //Ends the pawn's turn, preventing further actions and emitting the turn_ended signal
        void end_pawn_turn();
        //Sets the pawn's moving state and emits the pawn_moved signal if true
        //@param value: Whether the pawn is moving or not
        void set_moving(bool value);
        //Sets the pawn's attacking state and emits the pawn_attacked signal if false
        //@param value: Whether the pawn can attack or not
        void set_attacking(bool value);

    protected:
        static void _bind_methods() {
            //Signal emitted when the pawn attacks
            rl::signal_binding<TacticsPawnResource, tog::node::signal::TacticsPawnResource::pawn_attacked>::add<>();
            //Signal emitted when the pawn moves
            rl::signal_binding<TacticsPawnResource, tog::node::signal::TacticsPawnResource::pawn_moved>::add<>();
            //Signal emitted when the pawn's turn ends
            rl::signal_binding<TacticsPawnResource, tog::node::signal::TacticsPawnResource::turn_ended>::add<>();
        }

    public:
        //Minimum height difference required for the pawn to jump
        static constexpr int MIN_HEIGHT_TO_JUMP = 1;
        //Strength of gravity applied to the paw
        static constexpr int GRAVITY_STRENGTH = 6;
        //Minimum time required for an attack animation
        static constexpr int ANIMATION_FRAMES = 1;
        //Number of frames in the pawn's animation
        static constexpr float MIN_TIME_FOR_ATTACK = 1.0f;

        //Whether the pawn's HUD is currently enabled
        bool m_pawn_hud_enabled{false};
        //Whether the pawn can move
        bool m_can_move{true};
        //Whether the pawn can attack
        bool m_can_attack{true};
        //Whether the pawn is currently jumping
        bool m_is_jumping{false};
        //Whether the pawn is currently moving
        bool m_is_moving{false};
        //The direction the pawn is moving in
        godot::Vector3 m_move_direction{0,0,0};
        //Current gravity vector applied to the pawn
        godot::Vector3 m_gravity{0,0,0};
        //Delay before the pawn can perform its next action
        float m_wait_delay = 0.0f;
        // Speed at which the pawn walks
        int m_walk_speed = 8;
        //Stack of tiles representing the pawn's pathfinding route
        godot::Array m_pathfinding_tile_stack;


    };

}

