#include "tactics_pawn_sprite.hpp"

#include "core/constants.hpp"
#include "util/utility_vec.hpp"

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/classes/viewport.hpp"

void tog::TacticsPawnSprite::_ready() {
    //grab sub nodes when the current node is ready
    m_animation_tree = this->get_node<godot::AnimationTree>(tog::node::name::BattleTest::AnimationTree);
    m_character_ui_name_label = this->get_node<godot::Label3D>(tog::node::name::BattleTest::NameLabel);
}

void tog::TacticsPawnSprite::setup(tog::Stats* stats_node, godot::String expertise) {
    auto playback = godot::Object::cast_to<godot::AnimationNodeStateMachinePlayback>(m_animation_tree->get(tog::node::name::BattleTest::Playback));

    if (playback) {
        m_animator = playback;
    } else {
        return;
    }

    m_animator->start("IDLE");
    m_animation_tree->set_active(true);
    //todo: fix the image loading
    auto loaded_sprite_image = godot::Image::load_from_file(stats_node->m_sprite);
    if (!loaded_sprite_image->is_empty()) {
        this->set_texture(godot::ImageTexture::create_from_image(loaded_sprite_image));
    }

    m_character_ui_name_label->set_text(!stats_node->m_override_name.is_empty() ? stats_node->m_override_name : stats_node->m_expertise);
}

void tog::TacticsPawnSprite::start_animator(godot::Vector3 move_direction, bool is_jumping) {
    if (move_direction == get_zero_vector3()) {
        m_animator->travel("IDLE");
    } else if (is_jumping) {
        m_animator->travel("JUMP");
    }
}

void tog::TacticsPawnSprite::rotate_sprite(const godot::Basis& basis) {
    //Get forward vector of the camera (looking down the negative Z-axis)
    auto camera_forward = get_viewport()->get_camera_3d()->get_global_basis().get_column(2);
    //Measure how much the pawn faces towards or away from camera
    float scalar = basis.get_column(2).dot(camera_forward);
    //Determine if the sprite should be flipped horizontally
    set_flip_h(basis.get_column(0).dot(camera_forward) > 0);
    //Select appropriate sprite frame based on pawn orientation relative to camera
    if (scalar < -0.306) {
        //Pawn is facing away from camera, use base "back" frame
        this->set_frame(m_current_frame);
    } else if (scalar > 0.306) {
        //Facing towards camera, use "front" view
        this->set_frame(m_current_frame+ 1 * tog::TacticsPawnResource::ANIMATION_FRAMES);
    }
    //Note: If -0.306 <= scalar <= 0.306, the frame remains unchanged
}

bool tog::TacticsPawnSprite::adjust_to_center(tog::TacticsPawn* tactics_pawn) {
    if (tactics_pawn->get_tile() && tactics_pawn->m_tactics_pawn_resource->m_is_moving) {
        tactics_pawn->set_global_position(tactics_pawn->get_tile()->get_global_position());
        return true;
    }
    return false;
}
