#include "class_selection.hpp"

#include <godot_cpp/classes/dir_access.hpp>

#include "../resources/character/character_portrait.hpp"

namespace tog {

    ClassSelection::ClassSelection() {
        //reserve enough space in the array for all the roles
        m_roles.reserve(static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT));
        //create a resource for each class
        for (const int i : std::views::iota(0, static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT))) {
            m_roles.push_back(memnew(ClassStats));
            m_roles[i]->set_class_name(i);
        }
    }

    void ClassSelection::_ready() {
        //grab references to the related nodes needed
        m_role_selector = rl::gdcast<godot::Control>(this->get_parent()->find_child("RoleSelector", true, false));
        m_stat_container = rl::gdcast<godot::GridContainer>(this->get_parent()->find_child("StatsContainer", true, false));
        m_char_name_label = rl::gdcast<godot::Label>(this->get_parent()->find_child("CharNameLabel", true, false));
        m_char_name_label->add_theme_font_size_override("font_size", 64);
        m_char_image = rl::gdcast<godot::TextureRect>(this->get_parent()->find_child("CharImage", true, false));

        //bind button to appropriate callback functions
        //bind callback to transition to the player home screen
        auto* startButtonNode = rl::gdcast<godot::Button>(this->get_parent()->find_child("StartButton", true, false));
        rl::signal<rl::event::buttonPressed>::connect<godot::Button>(startButtonNode) <=> signal_callback(this, create_world);
        //bind callback to advance to the next character image from button press down event
        auto* nextCharacterButtonNode = rl::gdcast<godot::Button>(this->get_parent()->find_child("NextCharButton", true, false));
        rl::signal<rl::event::buttonPressed>::connect<godot::Button>(nextCharacterButtonNode) <=> signal_callback(this, on_next_character);
        //bind callback to decrease to the prev character image from button press down event
        auto* prevCharacterButtonNode = rl::gdcast<godot::Button>(this->get_parent()->find_child("PrevCharButton", true, false));
        rl::signal<rl::event::buttonPressed>::connect<godot::Button>(prevCharacterButtonNode) <=> signal_callback(this, on_prev_character);

        //cache
        hp_value_label = m_stat_container->get_node<godot::Label>("%HealthValue");
        mp_value_label = m_stat_container->get_node<godot::Label>("%ShinsuValue");
        attack_value_label = m_stat_container->get_node<godot::Label>("%AttackValue");
        magic_value_label = m_stat_container->get_node<godot::Label>("%PowerValue");
        defense_value_label = m_stat_container->get_node<godot::Label>("%DefenseValue");
        spirit_value_label = m_stat_container->get_node<godot::Label>("%SpiritValue");

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
        //compute slot positions around in a semi circle along y
        compute_slots();
        assign_items_to_slots(0);
        update_stats_display();

        //container to store the array of itmes
        load_character_images();
        update_character_display();
    }

    void ClassSelection::_physics_process(double delta) {

    }

    void ClassSelection::compute_slots() {
        m_slots.clear();
        float angles[5]   = { -0.6f, -0.3f, 0.0f, 0.3f, 0.6f };
        float scales[5]   = { 0.6f, 0.8f, 1.2f, 0.8f, 0.6f };
        int  z_values[5] = { 0, 1, 2, 1, 0 };
        // calculate the position of where the items will show up
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
        update_stats_display();
    }

    void ClassSelection::update_stats_display() {
        int selected_index = (m_curr_role_index + 2) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        hp_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_max_hp()));
        mp_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_max_mp()));
        attack_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_attack()));
        magic_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_magic_power()));
        defense_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_defense()));
        spirit_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_spirit_power()));
    }

    void ClassSelection::rotate_right() {
        //compute new offset going to the right
        int new_offset = (m_curr_role_index + 1) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        //animate_rotation(new_offset);
        //assign role to items with respect to offset
        m_curr_role_index = new_offset % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        assign_items_to_slots(new_offset);
        //update the position of the role we are currently at now
    }

    void ClassSelection::rotate_left() {
        //compute new offset going to the left
        int new_offset = (m_curr_role_index - 1) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        //animate_rotation(new_offset);
        if (new_offset <= -1)
            new_offset = static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT) - 1;
        //assign role to items with respect to offset
        m_curr_role_index = new_offset;
        assign_items_to_slots(new_offset);
    }

    void ClassSelection::animate_rotation() {
        //todo: animate the rotation?
    }

    void ClassSelection::on_next_character() {
        //advance the currently selected offset by 1
        if (m_char_port_container.is_empty()) {
            return;
        }
        // advance index and wrap around, similar to rotate_right()
        m_curr_char_image_index = ( m_curr_char_image_index + 1 ) % static_cast<int>(m_char_port_container.size());
        update_character_display();
    }

    void ClassSelection::on_prev_character() {
        //decrease the currently selected offset by 1
        if (m_char_port_container.is_empty()) {
            return;
        }
        // decrement and wrap around; add size before modulo to avoid negatives
        m_curr_char_image_index = (m_curr_char_image_index - 1 + static_cast<int>(m_char_port_container.size())) % static_cast<int>(m_char_port_container.size());
        update_character_display();
    }

    void ClassSelection::update_character_display() {
        m_console->print("The current character image index is: {} ", m_curr_char_image_index);
        godot::Dictionary entry = m_char_port_container[m_curr_char_image_index];
        if (m_char_image) {
            m_char_image->set_texture(entry["image"]);
            m_char_name_label->set_text(entry["id"]);
        }
    }

    void ClassSelection::load_character_images() {
        //grab the resource loader object
        godot::ResourceLoader* resource_loader = godot::ResourceLoader::get_singleton();
        //todo: find a better way to do a look up the project directory from anywhere
        const std::filesystem::path character_resource_path{"/Users/abi/CLionProjects/godot-jrpg/project/assets/resources/characters"};

        //iterate through the directory and load "character images" from the file
        for (const auto& file : std::filesystem::directory_iterator{character_resource_path}) {
            //check if resource loaded correctly
            godot::Ref<tog::CharacterPortraitSheet> loaded_char_sheet = resource_loader->load(file.path().c_str());
            assertion(loaded_char_sheet != nullptr, "Character Portrait Sheet Does Not Exist");

            //load character images into container
            godot::Array ids = loaded_char_sheet->get_ids();
            int character_count = loaded_char_sheet->get_count();

            for (int i{0}; i < character_count; i++) {
                //treating a "godot::directory" like a pair
                godot::Dictionary d;
                d["image"] = loaded_char_sheet->build_portrait_texture(i);
                d["id"] = ids[i];
                m_char_port_container.append(d);
            }
        }

        //we are passing in a variant type to contruct the godot::dictionary object
        for (godot::Dictionary x : m_char_port_container) {
            m_console->print("Character name loaded: {}", std::string(x["id"].stringify().utf8()) );
        }

    }

    void ClassSelection::create_world() {
        //save player data to a resource

        //save the player stats

        //save the character portarit too

        //change the scene to the
        m_console->print("Changing Scene to home_scene");
        godot::SceneTree* tree = get_tree();
        const godot::Error err = tree->change_scene_to_file(rl::path::ui::HomeScene);
    }

    [[signal_slot]]
    void ClassSelection::role_scroll(const godot::Ref<godot::InputEvent> &event) {
        godot::Ref<godot::InputEventMouseButton> mb = event;
        if (mb.is_valid() && mb->is_pressed() && mb->get_button_index() == godot::MouseButton::MOUSE_BUTTON_LEFT) {
            godot::Vector2 local = mb->get_position() - m_role_selector->get_global_position();
            float half = m_role_selector->get_size().x / 2.0f;
            if (local.x > half) {
                //going right
                m_console->print("Rotating right");
                rotate_right();
            } else {
                //going left
                m_console->print("Rotating left");
                rotate_left();
            }
        }
    }

}
