#include "main.hpp"

#include "core/constants.hpp"
#include "util/engine.hpp"
#include "util/utility.hpp"
#include "util/input.hpp"
#include "util/bind.hpp"
#include "util/scene.hpp"

#include "godot_cpp/classes/button.hpp"

namespace rl {

    Main::Main() {
        //load the scene from disk - is a packed scene resource, not a node at this point
        resource::preload::packed_scene<godot::Control> main_menu{ tog::path::scene::ui::MainMenu };
        //returns a tree of nodes that you can use as a child of your current node
        m_main_menu = main_menu.instantiate();

        if (m_main_menu) {
            //attach scene to current node as child
            tog::attach_child_to_parent(this, m_main_menu);

            //grab a reference to the "PlayButton" node in the "MainMenu" scene
            auto play_button_node = m_main_menu->get_node<godot::Button>(tog::node::name::MainMenu::PlayButton);
            //attach our callback function "load_character_creator_scene" to the "pressed" signal event of the respective node
            signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(play_button_node) <=> signal_callback(this, load_character_creator_scene);

            //grab a reference to the "QuitButton" node in the "MainMenu" scene
            auto quit_button_node = m_main_menu->get_node<godot::Button>(tog::node::name::MainMenu::QuitButton);
            //attach our callback function "stop_application" to the "pressed" signal event of the respective node
            signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(quit_button_node) <=> signal_callback(this, stop_application);

        } else {
            assertion(m_main_menu, "MainMenu scene does not exist");
        }
    }

    void Main::_ready() {
        this->apply_default_settings();
        //set the windows minimum size
        engine::root_window()->set_min_size(godot::Vector2i(1920, 1080));
    }

    void Main::_physics_process(double delta) {
        if (engine::editor_active())
            return;
    }

    [[signal_slot]]
    void Main::load_character_creator_scene() const {
        m_console->print("Loading Play Scene...");
        //grab the scene tree
        godot::SceneTree* tree = get_tree();
        //deattach the "main_menu" scene and then load the player creator
        tree->change_scene_to_file(tog::path::scene::ui::CharacterCreator);
    }

    [[signal_slot]]
    void Main::stop_application() const
    {
        m_console->print("Stopping Application .... ");
        get_tree()->get_root()->propagate_notification(godot::Window::NOTIFICATION_WM_CLOSE_REQUEST);
        get_tree()->quit(0);
    }

    void Main::apply_default_settings() {
        engine::set_fps(60);
        input::use_accumulated_inputs(false);
        if (not engine::editor_active()) {
            engine::root_window()->set_size({ 1920, 1080 });
            engine::root_window()->set_content_scale_mode(godot::Window::CONTENT_SCALE_MODE_VIEWPORT);
            engine::root_window()->set_content_scale_aspect(godot::Window::ContentScaleAspect::CONTENT_SCALE_ASPECT_IGNORE);
        }
    }
}
