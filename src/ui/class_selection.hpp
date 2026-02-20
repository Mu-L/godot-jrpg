#pragma once
#include <ranges>

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>

#include "core/constants.hpp"
#include "resources/class_stats.hpp"
#include "singletons/console.hpp"
#include "util/engine.hpp"
#include "util/io.hpp"

namespace tog {

    class ClassSelection : public godot::Node {
        GDCLASS(ClassSelection, godot::Node);

    private:
        struct Slot {
            godot::Vector2 position{};
            float scale{};
            int z{};
        };

    public:
        ClassSelection();
        ~ClassSelection() = default;

        void _ready() override;
        void _physics_process(double delta) override;

        [[signal_slot]] void role_scroll(const godot::Ref<godot::InputEvent>& event);

    protected:
        static void _bind_methods() {
            //expose callback to godot system
            godot::ClassDB::bind_method(godot::D_METHOD("role_scroll", "event"), &ClassSelection::role_scroll);
        }

    private:
        void compute_slots();
        void assign_items_to_slots(int offset);
        void update_stats_display();
        void rotate_right();
        void rotate_left();
        void animate_rotation();

    private:
        //how many items can be shown
        int m_visible_slots = 5;
        int m_curr_role_index = 0;
        int m_selected_role_index = 0;
        float m_radius = 120.0f;
        godot::Control* m_role_selector = nullptr;
        godot::GridContainer* m_stat_container = nullptr;
        godot::Label* hp_value_label = nullptr;
        godot::Label* mp_value_label = nullptr;
        godot::Label* attack_value_label = nullptr;
        godot::Label* magic_value_label = nullptr;
        godot::Label* defense_value_label = nullptr;
        godot::Label* spirit_value_label = nullptr;
        rl::Console<godot::RichTextLabel>* m_console{ rl::console::get() };
        std::vector<Slot> m_slots;
        std::vector<godot::Button*> m_items;
        godot::LocalVector<godot::Ref<ClassStats>> m_roles;
    };

}
