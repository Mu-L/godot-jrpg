#include "tactics_ui_service.hpp"

#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/v_box_container.hpp"

tog::TacticsUIService::TacticsUIService(const godot::Ref<tog::TacticsControlsResource>& controls_resource) {
    m_tactics_controls_resource = controls_resource;
}

void tog::TacticsUIService::update_controller_hints(tog::TacticsControls* tactics_controls) {
    //todo: texture loading does not working
    if (m_tactics_controls_resource->m_is_joystick) {
        //set to xbox controller layout
        //todo: change to a inline string var
        //tactics_controls->get_node<godot::TextureRect>(tog::node::name::BattleTest::ControllerHints)->set_texture(tactics_controls->m_layout_xbox_texture);
    } else {
        //set to pc layout
        //tactics_controls->get_node<godot::TextureRect>(tog::node::name::BattleTest::ControllerHints)->set_texture(tactics_controls->m_layout_pc_texture);
    }
}

void tog::TacticsUIService::set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn, tog::TacticsControls* tactics_controls) {
    //todo: change to an line
    if (!tactics_controls->get_node<godot::VBoxContainer>(tog::node::name::BattleTest::Actions)->is_visible()) {
        //Focus on Move action if menu wasn't visible
        tactics_controls->get_node<godot::Button>(tog::node::name::BattleTest::MoveButton)->grab_focus();
    }

    //Show menu if pawn can act
    tactics_controls->get_node<godot::VBoxContainer>(tog::node::name::BattleTest::Actions)->set_visible(v && tactics_pawn->can_act());

    //Exit if no pawn is provided
    if (!tactics_pawn) return;

    //Update action button states based on pawn's capabilities
    if ( godot::Button* move_button = tactics_controls->get_node<godot::Button>(tog::node::name::BattleTest::MoveButton); move_button ) {
        move_button->set_disabled( !tactics_pawn->m_tactics_pawn_resource->m_can_move );
    }

    if ( godot::Button* attack_button = tactics_controls->get_node<godot::Button>(tog::node::name::BattleTest::MoveButton); attack_button ) {
        attack_button->set_disabled( !tactics_pawn->m_tactics_pawn_resource->m_can_attack );
    }
}
