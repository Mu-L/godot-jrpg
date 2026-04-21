#include "tactics_main.hpp"
#include "core/constants.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "singletons/console.hpp"
#include "util/utility.hpp"

void tog::TacticsMain::_ready() {
    rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
    m_world_node = godot::Object::cast_to<godot::Node3D>(this->get_node_or_null(tog::node::name::BattleTest::World));
    if (m_world_node) {
        m_console->print("World exist");
    } else {
        m_console->print("World DOES NOT exist");
    }
    m_battle_button = godot::Object::cast_to<godot::Button>(this->get_node_or_null(tog::node::name::BattleTest::Battle_Button));
    if (m_battle_button) {
        m_console->print("BUTTON exist");
    } else {
        m_console->print("BUTTON DOES NOT exist");
    }
    m_battle_button->grab_focus();
    //m_battle_button->connect(tog::constants::node::signal::BaseButton::pressed, callable_mp(this, &TacticsMain::on_battle_button_pressed));
    rl::signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(m_battle_button) <=> signal_callback(this, on_battle_button_pressed);
}

void tog::TacticsMain::on_battle_button_pressed() {
    rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
    m_console->print("button exist");
    load_level();
}

void tog::TacticsMain::unload_level() {
    if (m_level_instance) {
        m_level_instance->queue_free();
    }
    m_level_instance = nullptr;
}

void tog::TacticsMain::load_level() {
    unload_level();
    godot::Ref<godot::PackedScene> level = godot::ResourceLoader::get_singleton()->load(tog::path::scene::Battle::Level::TestLevel);
    //m_world_node->add_child(level->instantiate());
    const auto node = level->instantiate();
    attach_child_to_parent(m_world_node, node);
    godot::Object::cast_to<godot::Control>(m_battle_button->get_parent())->set_visible(false);
}
