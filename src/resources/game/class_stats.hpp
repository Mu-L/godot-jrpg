#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "util/bind.hpp"
#include "core/attributes.hpp"

namespace tog {

    class ClassStats : public godot::Resource {
        GDCLASS(ClassStats, godot::Resource);

    public:
        enum class ClassName {
            FISHERMAN = 0,
            SPEAR_BEARER = 1,
            SCOUT = 2,
            LIGHT_BEARER = 3,
            WAVE_CONTROLLER = 4,
            JEONSULSA = 5,
            HWAYEOMSA = 6,
            DANSULSA = 7,
            WONSULSA = 8,
            ANIMA = 9,
            DEFENDER = 10,
            GUIDE = 11,
            MAX_CLASS_COUNT = 12
        };

    public:
        ClassStats() = default;
        ~ClassStats() override = default;

        [[property]] void set_max_hp(const int value);
        [[property]] void set_max_mp(const int value);
        [[property]] void set_attack(const int value);
        [[property]] void set_magic_power(const int value);
        [[property]] void set_defense(const int value);
        [[property]] void set_spirit_power(const int value);
        [[property]] void set_class_name(const int value);

        [[property]] int get_max_hp()                       { return m_max_hp; }
        [[property]] int get_max_mp()                       { return m_max_mp; }
        [[property]] int get_attack()                       { return m_attack; }
        [[property]] int get_magic_power()                  { return m_magic_power; }
        [[property]] int get_defense()                      { return m_defence; }
        [[property]] int get_spirit_power()                 { return m_spirit_power; }
        [[property]] int get_class_name()                   { return static_cast<int>(m_class_name); }

        std::string get_class_name_str() { return names[static_cast<int>(m_class_name)]; }

    protected:
        static void _bind_methods() {
            using namespace rl;
            bind_property(ClassStats, max_hp, int);
            bind_property(ClassStats, max_mp, int);
            bind_property(ClassStats, attack, int);
            bind_property(ClassStats, magic_power, int);
            bind_property(ClassStats, defense, int);
            bind_property(ClassStats, spirit_power, int);

            godot::ClassDB::bind_method(godot::D_METHOD("set_class_name", "p_speed"), &ClassStats::set_class_name);
            godot::ClassDB::bind_method(godot::D_METHOD("get_class_name"), &ClassStats::get_class_name);
            ADD_PROPERTY(godot::PropertyInfo(
                         godot::Variant::INT,
                         "Class Name",
                         godot::PROPERTY_HINT_ENUM,
                         "FISHERMAN,SPEAR_BEARER,SCOUT,LIGHT_BEARER,WAVE_CONTROLLER,JEONSULSA,HWAYEOMSA,DANSULSA,WONSULSA,ANIMA,DEFENDER,GUIDE"),
                         "set_class_name",
                         "get_class_name");
        }

    private:
        int m_max_hp = 10;
        int m_max_mp = 10;
        int m_attack = 10;
        int m_magic_power = 10;
        int m_defence = 10;
        int m_spirit_power = 10;
        std::vector<std::string> names = {
            "FISHERMAN",
            "SPEAR_BEARER",
            "SCOUT",
            "LIGHT_BEARER",
            "WAVE_CONTROLLER",
            "JEONSULSA",
            "HWAYEOMSA",
            "DANSULSA",
            "WONSULSA",
            "ANIMA",
            "DEFENDER",
            "GUIDE",
            "ERROR"
        };
        ClassName m_class_name{ClassName::MAX_CLASS_COUNT};
    };
}