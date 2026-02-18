#include "class_selection.hpp"

namespace tog {

    ClassSelection::ClassSelection() {
        using namespace rl;
        //reserve buffer for all class selections up front
        m_roles.reserve(static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT));
        //create a resource for each class
        for (const int i : std::views::iota(0, static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT))) {
            m_roles.push_back(memnew(ClassStats));
            m_roles[i]->set_class_name(i);
            m_console->print("Role attack is {} ", m_roles[i]->get_class_name_str());
        }

    }

    void ClassSelection::_ready() {
        //set needed nodes
        m_role_selector = rl::gdcast<godot::Control>(this->get_parent()->find_child("RoleSelector", true, false));
        m_stat_container = rl::gdcast<godot::GridContainer>(this->get_parent()->find_child("StatsContainer", true, false));

        //bind the signal for "gui_input" to be called our function
        rl::signal<rl::event::gui_input>::connect<godot::Control>(m_role_selector) <=> signal_callback(this, role_scroll);

        //initialize buttons to be used as selectables
        for (int i{0}; i < m_visible_slots; i++) {
            auto* new_button = memnew(godot::Button);

            m_role_selector->add_child(new_button);
            new_button->set_owner(m_role_selector);
            m_role_selector->set_editable_instance(new_button, true);

            m_items.push_back(new_button);
        }

        //compute slot positions around in a circle
        compute_slots();
        assign_items_to_slots(5);

    }

    void ClassSelection::_physics_process(double delta) {

    }

    void ClassSelection::compute_slots() {
        m_slots.clear();
        float angles[5]   = { -0.6f, -0.3f, 0.0f, 0.3f, 0.6f };
        //float angles[5]   = {-1.2f, -0.6f, 0.0f, 0.6f, 1.2f};
        float scales[5]   = { 0.6f, 0.8f, 1.2f, 0.8f, 0.6f };
        int  z_values[5] = { 0, 1, 2, 1, 0 };
        // calculate the positions of where the items will show up
        auto center = godot::Vector2(680.0/2 - m_radius, 230/2);
        for (int i{0}; i < m_visible_slots; i++) {
            Slot s;
            s.position = center + godot::Vector2(m_radius, 0).rotated(angles[i]);
            s.position.x = 680.0f/2.0f;
            s.scale = scales[i];
            s.z = z_values[i];
            m_slots.push_back(s);
        }
    }

    void ClassSelection::assign_items_to_slots(int offset) {

        for (int i{0}; i < m_visible_slots; i++) {
            int role_index = (offset + i) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
            m_items[i]->set_text(m_roles[role_index]->get_class_name_str().data());
            m_items[i]->set_scale(godot::Vector2(m_slots[i].scale, m_slots[i].scale));
            m_items[i]->set_position(m_slots[i].position);
            m_items[i]->set_z_index(m_slots[i].z);
        }
        m_curr_role_index = (offset + 2) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);

        update_stats_display();
    }

    void ClassSelection::update_stats_display() {

    }

    void ClassSelection::rotate_right() {
        int new_offset = (m_curr_role_index + 1) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
    }

    void ClassSelection::rotate_left() {
        int new_offset = (static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT) + m_curr_role_index - 1) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);

    }

    void ClassSelection::animate_rotation() {

    }

    [[signal_slot]]
    void ClassSelection::role_scroll(const godot::Ref<godot::InputEvent> &event) {
        godot::Ref<godot::InputEventMouseButton> mb = event;
        if (mb.is_null() || !mb->is_pressed() || mb->get_button_index() != godot::MouseButton::MOUSE_BUTTON_LEFT) {
            return;
        }
        m_console->print("You clicked the role scroll");
    }

}
