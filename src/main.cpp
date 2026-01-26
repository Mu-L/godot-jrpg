#include "core/assert.hpp"
#include "main.hpp"
#include "util/conversions.hpp"
#include "util/engine.hpp"
#include "util/input.hpp"

namespace rl
{
    Main::Main() {
        resource::preload::packed_scene<Level> level{ path::scene::Level1 };
        resource::preload::packed_scene<MainDialog> dialog{ path::ui::MainDialog };

        m_active_level = level.instantiate();
        runtime_assert(m_active_level != nullptr);
        m_main_dialog = dialog.instantiate();
        runtime_assert(m_main_dialog != nullptr);

        if (m_main_dialog != nullptr) {

            if (m_main_dialog != nullptr) {
                //add "MainDialog" scene to "Main" node as a child and make it show up in the editor
                this->add_child(m_main_dialog);
                m_main_dialog->set_owner(this);
                this->set_editable_instance(m_main_dialog, true);
            }

            m_canvas_layer = gdcast<godot::CanvasLayer>(m_main_dialog->find_child(name::dialog::canvas_layer, true, false));

            runtime_assert(m_canvas_layer != nullptr);
            if (m_active_level != nullptr && m_canvas_layer != nullptr) {
                m_canvas_layer->get_parent()->set_editable_instance(m_canvas_layer, true);
                m_canvas_layer->add_child(m_active_level);
                m_active_level->set_owner(m_canvas_layer);
                m_canvas_layer->set_editable_instance(m_active_level, true);
            }
        }
    }

    void Main::_ready() {
        this->apply_default_settings();
    }

    void Main::_physics_process(double delta) {
        if (engine::editor_active())
            return;

        m_signal_timer += delta;
        if (m_signal_timer > 1.0) {
            this->emit_signal(event::signal_example, delta);
            m_signal_timer -= 1.0;
        }
    }

    void Main::apply_default_settings() {
        engine::set_fps(60);
        input::use_accumulated_inputs(false);
        if (not engine::editor_active())
            engine::root_window()->set_size({ 1920, 1080 });
    }
}
