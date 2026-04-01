#pragma once

#include "util/bind.hpp"
#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //The attributes of a game actor
    class StatsResource : public godot::Resource {
        GDCLASS(StatsResource, godot::Resource);

        enum class Strategy {
            TANK,
            FLANK,
            PHYSICAL,
            DISTANCE,
            SUPPORT
        };

    public:
        StatsResource() = default;
        ~StatsResource() override = default;

        void set_override_name(const godot::String& value)  { m_override_name = value; }
        void set_expertise(const godot::String& value)      { m_expertise = value; }
        void set_strategy(const int value)                  { m_strategy = Strategy{value}; }
        void set_level(const int value)                     { m_level = value; }
        void set_sprite_path(const godot::String& value)    { m_sprite_path = value; }
        void set_movement(const int value)                  { m_movement = value; }
        void set_jump(const int value)                      { m_jump = m_movement / 2.0f; }
        void set_max_health(const int value)                { m_max_health = value; }
        void set_attack_range(const int value)              { m_attack_range = value; }
        void set_attack_power(const int value)              { m_attack_power = value; }

        godot::String get_override_name()   { return m_override_name; }
        godot::String get_expertise()       { return m_expertise; }
        int get_strategy()                  { return static_cast<int>(m_strategy); }
        int get_level() const               { return m_level; }
        godot::String get_sprite_path()     { return m_sprite_path; }
        int get_movement() const            { return m_movement; }
        float get_jump() const              { return m_jump; }
        int get_max_health() const          { return m_max_health; }
        int get_attack_range() const        { return m_attack_range; }
        int get_attack_power() const        { return m_attack_power; }

    protected:
        static void _bind_methods() {
            //bind property to editor
            rl::bind_property(StatsResource, override_name, godot::String);
            rl::bind_property(StatsResource, expertise, godot::String);
            godot::ClassDB::bind_method(godot::D_METHOD("set_strategy", "value"), &StatsResource::set_strategy);
            godot::ClassDB::bind_method(godot::D_METHOD("get_strategy"), &StatsResource::get_strategy);
            ADD_PROPERTY(
                godot::PropertyInfo(
                    godot::Variant::INT,
                    "strategy", godot::PROPERTY_HINT_ENUM,
                    "Tank,Flank,Physical,Distance,Support"),
                "set_strategy",
                "get_strategy");
            rl::bind_property(StatsResource, sprite_path, godot::String);
            rl::bind_property(StatsResource, movement, int);
            rl::bind_property(StatsResource, jump, int);
            rl::bind_property(StatsResource, max_health, int);
            rl::bind_property(StatsResource, attack_range, int);
            rl::bind_property(StatsResource, attack_power, int);
        }

    private:
        //Override name for the actor
        godot::String m_override_name;
        //Expertise of the actor
        godot::String m_expertise;
        //Strategy type of the actor
        Strategy m_strategy;
        //Current level of the actor
        int m_level = 1;
        //Path to the actor's sprite
        godot::String m_sprite_path;
        //Movement. Average: 3-5 (base). Endgame: 9 max.
        int m_movement = 3;
        //Jump height, calculated as half of movement
        float m_jump = m_movement/2.0f;
        //Maximum health of the actor
        int m_max_health = 5;
        //How far you can project your basic attack
        int m_attack_range = 1;
        //Attack power of the actor
        int m_attack_power = 1;
    };

}

