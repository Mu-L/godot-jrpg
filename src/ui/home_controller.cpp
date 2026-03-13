#include "home_controller.hpp"

#include "core/constants.hpp"

#include "godot_cpp/classes/resource_loader.hpp"
#include <godot_cpp/classes/label.hpp>


tog::HomeController::HomeController() {
    //load resource into
    m_main_player_state =  godot::ResourceLoader::get_singleton()->load(tog::path::resource::player::main_player);
}

void tog::HomeController::_ready() {
    //grab node references
    m_name_value = get_node<godot::Label>(tog::node::name::HomeScene::NameValue);
    m_level_value = get_node<godot::Label>(tog::node::name::HomeScene::LevelValue);
    m_hp_value = get_node<godot::Label>(tog::node::name::HomeScene::HPValue);
    m_shinsu_value = get_node<godot::Label>(tog::node::name::HomeScene::ShinsuValue);
    m_attack_value = get_node<godot::Label>(tog::node::name::HomeScene::AttackValue);
    m_defense_value = get_node<godot::Label>(tog::node::name::HomeScene::DefenseValue);
    m_magic_power_value = get_node<godot::Label>(tog::node::name::HomeScene::MagicPowerValue);
    m_spirit_power_value = get_node<godot::Label>(tog::node::name::HomeScene::SpiritPowerValue);
    m_main_char_name = get_node<godot::Label>(tog::node::name::HomeScene::MainPlayer);
    m_main_char_image = get_node<godot::TextureRect>(tog::node::name::HomeScene::MainPlayerImage);
    //display_character_info
    display_character_info();
}

void tog::HomeController::display_character_info() {
    m_name_value->set_text(m_main_player_state->get_name());
    m_main_char_name->set_text(m_main_player_state->get_name());
    m_main_char_image->set_texture(m_main_player_state->get_image());
    m_level_value->set_text(godot::String::num_int64(m_main_player_state->get_level()));
    m_hp_value->set_text(godot::String::num_int64(m_main_player_state->get_hp()));
    m_shinsu_value->set_text(godot::String::num_int64(m_main_player_state->get_shinsu()));
    m_attack_value->set_text(godot::String::num_int64(m_main_player_state->get_attack()));
    m_defense_value->set_text(godot::String::num_int64(m_main_player_state->get_defense()));
    m_magic_power_value->set_text(godot::String::num_int64(m_main_player_state->get_magic_power()));
    m_spirit_power_value->set_text(godot::String::num_int64(m_main_player_state->get_spirit_power()));
}
