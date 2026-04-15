#include "expertise.hpp"
#include "core/constants.hpp"

void tog::Expertise::_ready() {
    m_stats = godot::Object::cast_to<tog::Stats>(get_node_or_null(tog::constants::node::name::BattleTest::Stats_));
    m_stats->import_stats(m_starting_stats);
}

void tog::Expertise::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_starting_stats", "resource"), &Expertise::set_starting_stats);
    godot::ClassDB::bind_method(godot::D_METHOD("get_starting_stats"), &Expertise::get_starting_stats);
    ADD_PROPERTY(
        godot::PropertyInfo(
            godot::Variant::OBJECT,
            "m_starting_stats",
            godot::PROPERTY_HINT_RESOURCE_TYPE,
            tog::StatsResource::get_class_static()
        ),
        "set_starting_stats",
        "get_starting_stats"
    );

    godot::ClassDB::bind_method(godot::D_METHOD("set_starting_skills", "list"), &Expertise::set_starting_skills);
    godot::ClassDB::bind_method(godot::D_METHOD("get_starting_skills"), &Expertise::get_starting_skills);
    ADD_PROPERTY(
        godot::PropertyInfo(
            godot::Variant::ARRAY,
            "m_starting_skills",
            godot::PROPERTY_HINT_RESOURCE_TYPE,
            "String"
        ),
        "set_starting_skills",
        "get_starting_skills"
    );
}
