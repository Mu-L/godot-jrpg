#pragma once

#include "util/bind.hpp"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/classes/texture2d.hpp>

namespace tog {

    //container to represents the character's state
    class CharacterState : public godot::Resource {
        GDCLASS(CharacterState, godot::Resource);

    public:
        godot::String get_name()      { return m_name; }
        godot::String get_role()      { return m_role; }
        godot::Ref<godot::Texture2D> get_image() { return m_image; }
        int get_level()         const { return m_level; }
        int get_xp()            const { return m_xp; }
        int get_hp()            const { return m_hp; }
        int get_shinsu()        const { return m_shinsu; }
        int get_defense()       const { return m_defense; }
        int get_attack()        const { return m_attack; }
        int get_magic_power()   const { return m_magic_power; }
        int get_spirit_power()  const { return m_spirit_power; }

        void set_name(godot::String value)   { m_name = std::move(value); }
        void set_role(godot::String value)   { m_role = std::move(value); }
        void set_image(const godot::Ref<godot::Texture2D>& value)   { m_image = value; }
        void set_level(int value)            { m_level = value; }
        void set_xp(int value)               { m_xp = value; }
        void set_hp(int value)               { m_hp = value; }
        void set_shinsu(int value)           { m_shinsu = value; }
        void set_defense(int value)          { m_defense = value; }
        void set_attack(int value)           { m_attack = value; }
        void set_magic_power(int value)      { m_magic_power = value; }
        void set_spirit_power(int value)     { m_spirit_power = value; }

    protected:
        static void _bind_methods() {
            rl::bind_property(CharacterState, name, godot::String);
            rl::bind_property(CharacterState, role, godot::String);
            rl::bind_property(CharacterState, level, int);
            rl::bind_property(CharacterState, xp, int);
            rl::bind_property(CharacterState, hp, int);
            rl::bind_property(CharacterState, shinsu, int);
            rl::bind_property(CharacterState, defense, int);
            rl::bind_property(CharacterState, attack, int);
            rl::bind_property(CharacterState, magic_power, int);
            rl::bind_property(CharacterState, spirit_power, int);
            rl::bind_property(CharacterState, image, godot::Ref<godot::Texture2D>);
        }

    private:
        godot::String m_name{"default"};
        godot::String m_role{"default"};
        int m_level = 1;
        int m_xp = 0;
        int m_hp = 0;
        int m_shinsu = 0;
        int m_defense = 0;
        int m_attack = 0;
        int m_magic_power = 0;
        int m_spirit_power = 0;
        godot::Ref<godot::Texture2D> m_image{};
        godot::Array m_spells;
        godot::Dictionary inventory; //item_id -> item_quantity

    };
}
