#pragma once

#include "stats.hpp"
#include "resources/battle/stats_resource.hpp"
#include "godot_cpp/classes/node.hpp"

namespace tog {

    //The expertise of a game actor.
    //Assigns a set of stats to a pawn
    class Expertise : public godot::Node {
        GDCLASS(Expertise, godot::Node);

    public:
        Expertise() = default;
        ~Expertise() override = default;

        void _ready() override;

        void set_starting_skills(const godot::Array& skills) { m_starting_skills = skills; }
        godot::Array get_starting_skills() { return m_starting_skills; }

        void set_starting_stats(const godot::Ref<tog::StatsResource>& stats_resource) { m_starting_stats = stats_resource; }
        godot::Ref<tog::StatsResource> get_starting_stats() { return m_starting_stats; }

    protected:
        void static _bind_methods();

    private:
        //Resource containing initial stats for the actor
        godot::Ref<tog::StatsResource> m_starting_stats;
        //Array of initial skills for the actor
        godot::Array m_starting_skills;
        //Node containing the actor's stats
        tog::Stats* m_stats;
    };

}

