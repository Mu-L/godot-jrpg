#pragma once
#include "godot_cpp/classes/node.hpp"
#include "resources/battle/stats_resource.hpp"


namespace tog {

    //Placeholder script that essentially replicates the Pawn Expertise Model into its own self-contained Stats class.
    //his class can be made into a Resource Save utility for instantiated characters, for instance.
    //Alternatively, it could pull the appropriate data from a character save and write back to it as needed.
    class Stats : public godot::Node {
        GDCLASS(Stats, godot::Node);

    public:
        Stats() = default;
        ~Stats() override = default;

        //Initialize stats from a StatsResource
        void import_stats(godot::Ref<tog::StatsResource>& stats_resource);
        //Provided a health operation as a parameter (e.g. "-2", "1"), adds the value to current health.
        //As a consequence, this function serves for both damage and healing.
        void apply_to_current_health(int value);

    protected:
        static void _bind_methods() {}

    public:
        //Dictionary to store modifiers
        godot::Dictionary m_modifiers;
        //Override name for the character
        godot::String m_override_name;
        //Expertise of the character
        godot::String m_expertise;
        //Current level of the character
        int m_level = 1;
        //BASE STATS
        //Movement Points (The radius the pawn can move)
        int m_movement;
        //Jump height
        int m_jump;
        //Maximum health
        int m_max_health;
        //Current Health
        int m_current_health;
        //Sprite path
        godot::String m_sprite;
        //OFFENSIVE STATS
        //attack power
        int m_attack_power;
        //attack range
        int m_attack_range;
    };

}
