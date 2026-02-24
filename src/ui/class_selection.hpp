#pragma once
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "core/constants.hpp"
#include "resources/class_stats.hpp"
#include "singletons/console.hpp"
#include "util/engine.hpp"
#include "util/io.hpp"

#include <ranges>

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
            //let godot engine know we can call this function
            rl::bind_member_function(ClassSelection, create_world);
        }

    private:
        //initialize buttons to be used as role selectors
        void compute_slots();
        //assign the roles to the buttons
        void assign_items_to_slots(int offset);
        //updates the stats panel and its child nodes with their respective values
        void update_stats_display();
        //rotate the roles selector to the right
        void rotate_right();
        //rotate the roles selector to the left
        void rotate_left();
        //animation for switching between roles
        void animate_rotation();

        //change to "home_scene" (creates the game world)
        void create_world();

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
