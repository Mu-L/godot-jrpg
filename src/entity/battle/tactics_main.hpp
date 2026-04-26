#pragma once

#include "singletons/console.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/texture_rect.hpp"

namespace tog {

    class TacticsLevel;

    //A placeholder script that is meant to be replaced by your own level loader system
    class TacticsMain : public godot::Node {
        GDCLASS(TacticsMain, godot::Node);

    public:
        TacticsMain() = default;
        ~TacticsMain() override = default;

        void _ready() override;

        void on_battle_button_pressed();

    private:

        void unload_level();

        void load_level();

        void add_input_map_actions(const godot::StringName& action, godot::Key key, float deadzone = 0.2f);

    protected:
        void static _bind_methods() {
            rl::bind_member_function(TacticsMain, on_battle_button_pressed);
        };

    private:
        //The current instance of the TacticsLevel
        tog::TacticsLevel*  m_level_instance = nullptr;
        //Reference to the World node
        godot::Node3D*      m_world_node = nullptr;
        //Reference to the demo map button
        godot::Button*      m_battle_button = nullptr;
        //reference to the background image node
        godot::TextureRect* m_background_image = nullptr;
        rl::Console<godot::RichTextLabel>*          m_console{ rl::console::get() };

    };

}


