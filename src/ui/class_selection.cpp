#include <ranges>

#include "class_selection.hpp"
#include "util/io.hpp"

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

        //initialize buttons to be used as selectables
        for (int i{0}; i < m_visible_slots; i++) {
            m_items.push_back(memnew(godot::Button));
        }

    }

    void ClassSelection::_ready() {
        m_console->print("Class Selection Ready");

        auto* role_selector = rl::gdcast<godot::Control>(this->get_parent()->find_child("RoleSelector", true, false));



        //compute slot positions around in a circle
        compute_slots();
        assign_items_to_slots(5);

    }

    void ClassSelection::_physics_process(double delta) {

    }

    void ClassSelection::compute_slots() {
        m_slots.clear();
        float angles[5]   = { -0.5f, -0.25f, 0.0f, 0.25f, 0.5f };
        float scales[5]   = { 0.6f, 0.8f, 1.2f, 0.8f, 0.6f };
        int  z_values[5] = { 0, 1, 2, 1, 0 };

        auto center = godot::Vector2(0, 0);
        //calculate the positions of where the items will show up
        for (int i{0}; i < m_visible_slots; i++) {
            Slot s;
            s.position = center + godot::Vector2(m_radius, 0).rotated(angles[i]);
            s.scale = scales[i];
            s.z = z_values[0];
            m_slots.push_back(s);
        }

    }

    void ClassSelection::assign_items_to_slots(int offset) {

        for (int i{0}; i < m_visible_slots; i++) {
            int role_index = (offset + i) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
            m_items[i]->set_text(m_roles[role_index]->get_class_name_str().data());
            m_items[i]->set_position(m_slots[i].position);
            m_items[i]->set_scale(godot::Vector2(m_slots[i].scale, m_slots[i].scale));
            m_items[i]->set_z_index(m_slots[i].z);
        }

        m_curr_role_index = (offset + 2) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
    }

    void ClassSelection::update_stats_display() {
    }

}
