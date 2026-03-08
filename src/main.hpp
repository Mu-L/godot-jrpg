#pragma once
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/button.hpp"

#include <utility>
#include "entity/level.hpp"
#include "ui/main_dialog.hpp"

namespace rl {

    class Main : public godot::Node {
        GDCLASS(Main, godot::Node);

    public:
        Main();
        ~Main() override = default;

        void _ready() override;
        void _physics_process(double delta) override;

        [[signal_slot]] void load_character_creator_scene() const;
        [[signal_slot]] void stop_application() const;

    protected:
        void apply_default_settings();

        static void _bind_methods() {
            bind_member_function(Main, load_character_creator_scene);
            bind_member_function(Main, stop_application);
        }

    private:
        godot::Control* m_main_menu;
        Console<godot::RichTextLabel>* m_console{ console::get() };
    };

}
