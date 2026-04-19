#pragma once

#include "entity/battle/tactics_main.hpp"
#include "resources/character/character_state.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/texture_rect.hpp"
#include "singletons/console.hpp"

namespace tog {

    //load the main_player resource and manages the players game home screen
    class HomeController : public godot::Node {
        GDCLASS(HomeController, godot::Node);

    public:
        HomeController();
        ~HomeController() override = default;

        void _ready() override;

    protected:
        static void _bind_methods() {}

    private:
        //display character stats loaded from resource
        void display_character_info();
        //load the "tactics_battle" feature upon click
        void on_battle_button_press();

    private:
        godot::Label* m_name_value{nullptr};
        godot::Label* m_level_value{nullptr};
        godot::Label* m_hp_value{nullptr};
        godot::Label* m_shinsu_value{nullptr};
        godot::Label* m_attack_value{nullptr};
        godot::Label* m_defense_value{nullptr};
        godot::Label* m_magic_power_value{nullptr};
        godot::Label* m_spirit_power_value{nullptr};
        godot::Label* m_main_char_name{nullptr};
        godot::TextureRect* m_main_char_image{nullptr};
        godot::Ref<tog::CharacterState> m_main_player_state{};
        rl::Console<godot::RichTextLabel>* m_console{ rl::console::get() };
        tog::TacticsMain* m_tactics_battle_entry;

    };

}
