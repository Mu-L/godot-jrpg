#pragma once

#include "resources/game/class_stats.hpp"
#include "singletons/console.hpp"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/label.hpp>
#include "godot_cpp/classes/texture_rect.hpp"
#include <godot_cpp/classes/input_event.hpp>

/*
 *  todo: violating single responsibility rule
 *  currently this class is used to cycle between two different arrays to represent a selected class/character
 *  as well as to load/save the main player character state
 *  it also creates default selectable pickable "classes" and "characters"
 *  could probably find a better way to handle this
 *  but before doing this i probably wanna make the "class" selection a bit cleaner
 */

namespace tog {

    class ClassSelection : public godot::Node {
        GDCLASS(ClassSelection, godot::Node);

    private:
        struct ElementTransform {
            godot::Vector2 position{};
            float scale{};
            int z{};
        };

    public:
        ClassSelection();
        ~ClassSelection() override = default;

        void _ready() override;

        void role_scroll(const godot::Ref<godot::InputEvent>& event);

    protected:

        static void _bind_methods() {
            //expose callback to godot system and let godot system know how to call it
            rl::bind_member_function(ClassSelection, role_scroll);
            rl::bind_member_function(ClassSelection, create_world);
            rl::bind_member_function(ClassSelection, on_next_character);
            rl::bind_member_function(ClassSelection, on_prev_character);
        }

    private:
        //initialize buttons to be used as role selectors
        void compute_slots();
        //assign the roles to the buttons
        void assign_items_to_slots(int offset);
        //updates the stats panel and its child nodes with their respective values
        void update_stats_display();
        //animation for switching between roles
        void animate_rotation();
        //callback function for when the "next" button is click for selecting character
        void on_next_character();
        //callback function for when the "prev" button is click for selecting character
        void on_prev_character();
        //update character display
        void update_character_display();
        //load character images into an array from files
        void load_character_images();
        //change to "home_scene" (creates the game world)
        void create_world();

    private:
        int m_visible_slots{5};
        int m_curr_role_index{0};
        int m_curr_char_image_index{0};
        float m_radius{120.0f};
        godot::Control* m_role_selector{nullptr};
        godot::Label* m_hp_value_label{nullptr};
        godot::Label* m_shinsu_value_label{nullptr};
        godot::Label* m_attack_value_label{nullptr};
        godot::Label* m_magic_value_label{nullptr};
        godot::Label* m_defense_value_label{nullptr};
        godot::Label* m_spirit_value_label{nullptr};
        godot::Label* m_char_name_label{nullptr};
        godot::TextureRect* m_char_image{nullptr};
        rl::Console<godot::RichTextLabel>* m_console{ rl::console::get() };
        godot::Array m_char_port_container; //stores Dictionary entries like {"image": <Ref<Texture2D>, "id": <StringName>}
        std::vector<ElementTransform> m_slots;
        std::vector<godot::Button*> m_items;
        godot::LocalVector<godot::Ref<ClassStats>> m_roles;
    };

}
