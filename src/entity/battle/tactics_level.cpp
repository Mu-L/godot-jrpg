#include "tactics_level.hpp"

#include "tactics_participant.hpp"
#include "tactics_player.hpp"
#include "tactics_opponent.hpp"
#include "tactics_arena.hpp"

#include "resources/battle/tactics_camera_resource.hpp"

#include "godot_cpp/classes/resource_loader.hpp"
#include "util/engine.hpp"

void tog::TacticsLevel::_ready() {
    auto resource_loader = godot::ResourceLoader::get_singleton();

    m_tactics_camera_resource = resource_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_controls_resource = resource_loader->load(tog::path::resource::battle::tactics_control_resource);

    //Initialize node references
    m_tactics_participant   = godot::Object::cast_to<tog::TacticsParticipant>(get_node_or_null(tog::node::name::BattleTest::TacticsParticipant));
    m_tactics_player        = godot::Object::cast_to<tog::TacticsPlayer>(get_node_or_null(tog::node::name::BattleTest::TacticsPlayer));
    m_tactics_opponent      = godot::Object::cast_to<tog::TacticsOpponent>(get_node_or_null(tog::node::name::BattleTest::TacticsOpponent));
    m_tactics_arena         = godot::Object::cast_to<tog::TacticsArena>(get_node_or_null(tog::node::name::BattleTest::TacticsArena));

    //Configure arena tiles
    //m_tactics_arena->configure_tiles();
    //Configure participant with camera and UI control
    //m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);

    //Update camera boundary radius if necessary
    if (m_tactics_camera_resource->m_boundary_radius != m_camera_boundary_radius) {
        m_tactics_camera_resource->m_boundary_radius = m_camera_boundary_radius;
    }

}

void tog::TacticsLevel::_physics_process(double p_delta) {
    if (not rl::engine::editor_active()) {
        switch (m_turn_stage){
            case 0:
                //Initialize turn
                init_turn();
            case 1:
                //Handle ongoing turn
                handle_turn(p_delta);
            default: ;
        }
    }
}

void tog::TacticsLevel::init_turn() {
    if ( m_tactics_participant->is_configured(m_tactics_player) && m_tactics_participant->is_configured(m_tactics_opponent) ) {
        //Move to turn handling stage if both player and opponent are configured
        m_turn_stage = 1;
    }
}

void tog::TacticsLevel::handle_turn(float delta) {

    if (m_tactics_participant->can_act(m_tactics_player)) {

        if ( !m_tactics_participant->is_configured(m_tactics_player) ) {
            m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);
        }
        m_tactics_participant->act(delta, true, m_tactics_player);

    } else if (m_tactics_participant->can_act(m_tactics_opponent)) {

        if ( !m_tactics_participant->is_configured(m_tactics_opponent) ) {
            m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);
        }
        m_tactics_participant->act(delta, false, m_tactics_opponent);

    } else {

        m_tactics_player->reset_turn(m_tactics_player);
        m_tactics_opponent->reset_turn(m_tactics_opponent);

    }
}
