#pragma once

#include "stats.hpp"

#include "godot_cpp/classes/animation_node_state_machine_playback.hpp"
#include "godot_cpp/classes/animation_tree.hpp"
#include <godot_cpp/core/class_db.hpp>

#include "tactics_pawn.hpp"
#include "godot_cpp/classes/label3d.hpp"
#include "godot_cpp/classes/sprite3d.hpp"

namespace godot {
    class AnimationNodeStateMachinePlayback;
}

namespace tog {

    //Handles the visual representation and animation of a pawn in the tactics game
    class TacticsPawnSprite : public godot::Sprite3D {
        GDCLASS(TacticsPawnSprite, godot::Sprite3D);

    public:

        TacticsPawnSprite() = default;
        ~TacticsPawnSprite() override = default;

        void _ready() override;
        //Sets up the pawn sprite with the given stats and expertise
        //@param stats: The Stats resource containing pawn data
        //@param expertise: The pawn's expertise (class or type)
        void setup(tog::Stats* stats_node, godot::String expertise);
        //Starts the appropriate animation based on the pawn's movement and state
        //@param move_direction: The direction the pawn is moving in
        //@param is_jumping: Whether the pawn is currently jumping
        void start_animator(godot::Vector3 move_direction, bool is_jumping);
        //Rotates the sprite to face the camera and selects the appropriate frame
        //@param _global_basis: The global basis of the pawn
        void rotate_sprite(godot::Basis global_basis);
        //Adjusts the pawn's position to the center of its current tile
        //@param pawn: The TacticsPawn to adjust
        //@return: Whether the adjustment was successful
        bool adjust_to_center(tog::TacticsPawn* tactics_pawn);


    protected:
        static void _bind_methods() {}

    private:
        //Animation state machine playback controller
        godot::AnimationNodeStateMachinePlayback* m_animator = nullptr;
        //Current frame of the sprite animation
        int m_current_frame = 0;
        //Reference to the AnimationTree node
        godot::AnimationTree* m_animation_tree = nullptr;
        //Reference to the Label3D node displaying the pawn's name
        godot::Label3D* m_character_ui_name_label = nullptr;

    };

}

