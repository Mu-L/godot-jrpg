#pragma once
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/panel.hpp>
#include "resources/class_stats.hpp"
#include "singletons/console.hpp"

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

    protected:
        static void _bind_methods() {}

    private:
        void compute_slots();
        void assign_items_to_slots(int offset);
        void update_stats_display();



    private:
        //how many items can be shown
        int m_visible_slots = 5;
        int m_curr_role_index = 0;
        float m_radius = 120.0f;
        godot::Panel* m_class_panel = nullptr;
        rl::Console<godot::RichTextLabel>* m_console{ rl::console::get() };
        std::vector<Slot> m_slots;
        std::vector<godot::Button*> m_items;
        godot::LocalVector<godot::Ref<ClassStats>> m_roles;
    };

}
