#include "tactics_pawn_sprite.hpp"

#include "core/constants.hpp"

void tog::TacticsPawnSprite::_ready() {
    //grab sub nodes when the current node is ready
    m_animation_tree = this->get_node<godot::AnimationTree>(tog::node::name::BattleTest::AnimationTree);
    m_character_ui_name_label = this->get_node<godot::Label3D>(tog::node::name::BattleTest::NameLabel);
}

void tog::TacticsPawnSprite::setup(tog::Stats *stats_node, godot::String expertise) {
    auto playback = m_animation_tree->get_node<godot::AnimationNodeStateMachinePlayback>(tog::node::name::BattleTest::Playback);

    if (playback) {
        m_animator = playback;
    } else {
        assertion(false, "Playback node not found");
    }

    m_animator->start("IDLE");

}
