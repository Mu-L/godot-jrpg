#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/button.hpp"


#include "entity/level.hpp"
#include "ui/main_dialog.hpp"

namespace rl {

    class Main : public godot::Node {
        GDCLASS(Main, godot::Node);

    public:
        Main();
        ~Main() = default;

        void _ready() override;
        void _physics_process(double delta) override;

        [[signal_slot]] void loadPlayScene();

        [[signal_slot]] void loadSettingsScene();

        [[signal_slot]] void loadCreditsScene();

        [[signal_slot]] void quitGame();


    protected:
        void apply_default_settings();

        static void _bind_methods() {
            //this actually creates the binding
            //signal_binding<Main, event::signal_example>::add<double>();
            bind_member_function(Main, loadPlayScene);
            bind_member_function(Main, loadSettingsScene);
            bind_member_function(Main, loadCreditsScene);
            bind_member_function(Main, quitGame);
            //signal_binding<Main, event::changeToPlayScene>::add();
        }

    private:
        godot::Control* m_main_menu;
        Console<godot::RichTextLabel>* console{ console::get() };

        //keep for testing
        double m_signal_timer{ 0.0 };
        godot::CanvasLayer* m_canvas_layer{ nullptr };
        MainDialog* m_main_dialog{ nullptr };
        Level* m_active_level{ nullptr };
    };

}
