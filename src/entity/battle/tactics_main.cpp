#include "tactics_main.hpp"

#include "tactics_level.hpp"

#include "core/constants.hpp"
#include "util/utility.hpp"

#include "godot_cpp/classes/input_event_key.hpp"
#include "godot_cpp/classes/input_event_mouse_button.hpp"
#include "godot_cpp/classes/input_map.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"

void tog::TacticsMain::_ready() {
    //grab refence to world node
    m_world_node        = godot::Object::cast_to<godot::Node3D>(this->get_node_or_null(tog::node::name::BattleTest::World));

    //grab refence to background image node
    m_background_image  = godot::Object::cast_to<godot::TextureRect>(this->get_node_or_null(tog::constants::node::name::BattleTest::BackgroundImage));

    //grab reference to battle button and bind the "load level" callback function to the pressed down event
    m_battle_button     = godot::Object::cast_to<godot::Button>(this->get_node_or_null(tog::node::name::BattleTest::Battle_Button));
    m_battle_button->connect(tog::constants::node::signal::BaseButton::pressed, callable_mp(this, &TacticsMain::on_battle_button_pressed));

    //set the currently selected ui element to the battle_button
    m_battle_button->grab_focus();

    //add actions to input map
    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_left, godot::KEY_A);
    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_right, godot::KEY_D);
    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_forward, godot::KEY_W);
    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_backward, godot::KEY_S);

    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_rotate_left, godot::KEY_Q);
    bind_key_to_action(tog::node::signal::TacticsCaptureResource::camera_rotate_right, godot::KEY_E);

    bind_key_to_action(tog::node::signal::TacticsCaptureResource::controller_hints, godot::KEY_BACKSLASH);

    bind_mouse_button_to_action(tog::node::signal::TacticsCaptureResource::camera_free_look, godot::MOUSE_BUTTON_MIDDLE);
    bind_mouse_button_to_action(tog::node::signal::TacticsCaptureResource::ui_accept, godot::MOUSE_BUTTON_LEFT);
}

void tog::TacticsMain::on_battle_button_pressed() {
    load_level();
}

void tog::TacticsMain::unload_level() {
    //free node & sub children
    if (m_level_instance) m_level_instance->queue_free();
    m_level_instance = nullptr;
}

void tog::TacticsMain::load_level() {
    unload_level();
    //load test_level scene as a packed resource
    godot::Ref<godot::PackedScene> level = godot::ResourceLoader::get_singleton()->load(tog::path::scene::Battle::Level::TestLevel);
    const auto node = level->instantiate();
    attach_child_to_parent(m_world_node, node);
    godot::Object::cast_to<godot::Control>(m_battle_button->get_parent())->set_visible(false);
    m_background_image->set_visible(false);
}

void tog::TacticsMain::bind_key_to_action(const godot::StringName &action, godot::Key key, float deadzone) {
    godot::InputMap* input_map = godot::InputMap::get_singleton();

    //create mapping for incoming action
    if ( !input_map->has_action(action) ) {
        m_console->print("action created in InputMap {}", to_std_string(action));
        input_map->add_action(action, deadzone);
    }

    //create event model to be passed to
    godot::Ref<godot::InputEventKey> event;
    event.instantiate();
    event->set_keycode(key);

    //bind event key to action
    if ( !input_map->action_has_event(action, event) ) {
        m_console->print("event has bound to action {}", to_std_string(action));
        input_map->action_add_event(action, event);
    }

}

void tog::TacticsMain::bind_mouse_button_to_action(const godot::StringName &action, godot::MouseButton mouse_button, float deadzone) {
    godot::InputMap* input_map = godot::InputMap::get_singleton();
    //create mapping for incoming action
    if ( !input_map->has_action(action) ) {
        m_console->print("action created in InputMap {}", to_std_string(action));
        input_map->add_action(action, deadzone);
    }

    //create event model to be passed to
    godot::Ref<godot::InputEventMouseButton> event;
    event.instantiate();
    event->set_button_index(mouse_button);

    //bind event key to action
    if ( !input_map->action_has_event(action, event) ) {
        m_console->print("event has bound to action {}", to_std_string(action));
        input_map->action_add_event(action, event);
    }
}
