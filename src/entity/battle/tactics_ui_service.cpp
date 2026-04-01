#include "tactics_ui_service.hpp"

#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/v_box_container.hpp"

tog::TacticsUIService::TacticsUIService(const godot::Ref<tog::TacticsControlsResource>& controls_resource) {
    m_tactics_controls_resource = controls_resource;
}

void tog::TacticsUIService::update_controller_hints(tog::TacticsControls* tactics_controls) {
    if (m_tactics_controls_resource->m_is_joystick) {
        //set to xbox controller layout
        //todo: change to a inline string var
        tactics_controls->get_node<godot::TextureRect>("%ControllerHints")->set_texture(tactics_controls->m_layout_xbox_texture);
    } else {
        //set to pc layout
        tactics_controls->get_node<godot::TextureRect>("%ControllerHints")->set_texture(tactics_controls->m_layout_pc_texture);
    }
}

void tog::TacticsUIService::set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn, tog::TacticsControls* tactics_controls) {
    //todo: change to an line
    if (!tactics_controls->get_node<godot::VBoxContainer>("HBox/Actions")->is_visible()) {
        tactics_controls->get_node<godot::Button>("HBox/Actions/Move")->grab_focus();
    }

    tactics_controls->get_node<godot::VBoxContainer>("HBox/Actions")->set_visible(v);
    //tactics_pawn->can_act();

    if (!tactics_pawn) {
        return;
    }
    
}
