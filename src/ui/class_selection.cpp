#include "class_selection.hpp"

#include "resources/character/character_portrait.hpp"
#include "util/utility.hpp"

#include <godot_cpp/classes/dir_access.hpp>

namespace tog {

    ClassSelection::ClassSelection() {
        //reserve enough space in the array for all the roles
        m_roles.reserve(static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT));

        //create a resource "ClassStats" for each role we defined
        for (const int i : std::views::iota(0, static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT))) {
            auto* new_class_stats_resource = memnew(ClassStats);
            new_class_stats_resource->set_class_name(i);
            m_roles.push_back(new_class_stats_resource);
        }
    }

    void ClassSelection::_ready() {
        //grab references to the respective nodes needed
        m_role_selector         = get_node<godot::Control>      (tog::node::name::CharacterCreator::RoleContainer);
        m_char_name_label       = get_node<godot::Label>        (tog::node::name::CharacterCreator::CharNameLabel);
        m_char_image            = get_node<godot::TextureRect>  (tog::node::name::CharacterCreator::CharImage);
        m_hp_value_label        = get_node<godot::Label>        (tog::node::name::CharacterCreator::HealthValue);
        m_shinsu_value_label    = get_node<godot::Label>        (tog::node::name::CharacterCreator::ShinsuValue);
        m_attack_value_label    = get_node<godot::Label>        (tog::node::name::CharacterCreator::AttackValue);
        m_magic_value_label     = get_node<godot::Label>        (tog::node::name::CharacterCreator::PowerValue);
        m_defense_value_label   = get_node<godot::Label>        (tog::node::name::CharacterCreator::DefenseValue);
        m_spirit_value_label    = get_node<godot::Label>        (tog::node::name::CharacterCreator::SpiritValue);
        auto* start_button_node = get_node<godot::Button>       (tog::node::name::CharacterCreator::StartButton);
        auto* next_char_button  = get_node<godot::Button>       (tog::node::name::CharacterCreator::NextCharButton);
        auto* next_prev_button  = get_node<godot::Button>       (tog::node::name::CharacterCreator::PrevCharButton);

        //make the font bigger in label
        m_char_name_label->add_theme_font_size_override("font_size", 64);

        //-- bind button to appropriate callback functions
        //bind callback to transition to the player home screen
        rl::signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(start_button_node) <=> signal_callback(this, create_world);
        //bind callback to advance to the next character image from button press down event
        rl::signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(next_char_button) <=> signal_callback(this, on_next_character);
        //bind callback to decrease to the prev character image from button press down event
        rl::signal<tog::node::signal::BaseButton::pressed>::connect<godot::Button>(next_prev_button) <=> signal_callback(this, on_prev_character);
        //bind the signal for "gui_input" to be called our function
        rl::signal<tog::node::signal::Control::gui_input>::connect<godot::Control>(m_role_selector) <=> signal_callback(this, role_scroll);

        //initialize new godot::buttons and attach them to the RoleContainer node
        for (int i{0}; i < m_visible_slots; i++) {
            auto* new_button = memnew(godot::Button);
            tog::attach_child_to_parent(m_role_selector, new_button);
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

    void ClassSelection::compute_slots() {
        m_slots.clear();
        float angles[5]     = { -0.6f, -0.3f, 0.0f, 0.3f, 0.6f };
        float scales[5]     = { 0.6f, 0.8f, 1.2f, 0.8f, 0.6f };
        int  z_values[5]    = { 0, 1, 2, 1, 0 };
        // calculate the position of where the items will show up
        auto center = godot::Vector2(680.0/2 - m_radius, 230/2);
        for (const int i : std::views::iota(0,m_visible_slots)) {
            ElementTransform s;
            s.position = center + godot::Vector2(m_radius, 0).rotated(angles[i]);
            s.position.x = 680.0f/2.0f;
            s.scale = scales[i];
            s.z = z_values[i];
            m_slots.push_back(s);
        }
    }

    void ClassSelection::assign_items_to_slots(int offset) {
        for (const int i : std::views::iota(0,m_visible_slots)) {
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
        m_hp_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_max_hp()));
        m_shinsu_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_max_mp()));
        m_attack_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_attack()));
        m_magic_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_magic_power()));
        m_defense_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_defense()));
        m_spirit_value_label->set_text(godot::String::num_int64(m_roles[selected_index]->get_spirit_power()));
    }

    void ClassSelection::rotate_right() {
        //compute new offset going to the right
        m_curr_role_index = (m_curr_role_index + 1) % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        //animate_rotation(new_offset);
        //assign role to items with respect to offset
        assign_items_to_slots(m_curr_role_index);
    }

    void ClassSelection::rotate_left() {
        //compute new offset going to the left
        m_curr_role_index = (m_curr_role_index - 1 + static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT))
        % static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT);
        //animate_rotation(new_offset);
        //assign role to items with respect to offset
        assign_items_to_slots(m_curr_role_index);
    }

    void ClassSelection::animate_rotation() {
        //todo: animate the rotation?
    }

    void ClassSelection::on_next_character() {
        // advance index and wrap around, similar to rotate_right()
        m_curr_char_image_index = ( m_curr_char_image_index + 1 ) % static_cast<int>(m_char_port_container.size());
        update_character_display();
    }

    void ClassSelection::on_prev_character() {
        // decrement and wrap around; add size before modulo to avoid negatives
        m_curr_char_image_index = (m_curr_char_image_index - 1 + static_cast<int>(m_char_port_container.size())) % static_cast<int>(m_char_port_container.size());
        update_character_display();
    }

    void ClassSelection::update_character_display() {
        m_console->print("The current character image index is: {} ", m_curr_char_image_index);
        if (godot::Dictionary entry{m_char_port_container[m_curr_char_image_index]}; m_char_image) {
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
