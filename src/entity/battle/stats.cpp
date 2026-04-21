#include "stats.hpp"

void tog::Stats::import_stats(godot::Ref<tog::StatsResource>& stats_resource) {
    m_override_name = stats_resource->get_override_name();
    m_expertise = stats_resource->get_expertise();
    m_level = stats_resource->get_level();
    m_movement = stats_resource->get_movement();
    m_max_health = stats_resource->get_max_health();
    m_current_health = stats_resource->get_max_health();
    m_sprite = stats_resource->get_sprite_path();
    m_attack_power = stats_resource->get_attack_power();
    m_attack_range = stats_resource->get_attack_range();
}

void tog::Stats::apply_to_current_health(int value) {
    m_current_health = godot::Math::clamp(m_current_health + value, 0, m_max_health);
}
