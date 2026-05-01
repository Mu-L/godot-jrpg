#include "tactics_level.hpp"

#include "tactics_participant.hpp"
#include "tactics_player.hpp"
#include "tactics_opponent.hpp"
#include "tactics_arena.hpp"

#include "resources/battle/tactics_camera_resource.hpp"

#include "godot_cpp/classes/resource_loader.hpp"
#include "util/engine.hpp"

void tog::TacticsLevel::_ready() {
    m_logger->log()->print("called tog::TacticsLevel::_ready()");
    auto resource_loader = godot::ResourceLoader::get_singleton();

    m_tactics_camera_resource = resource_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_controls_resource = resource_loader->load(tog::path::resource::battle::tactics_control_resource);

    //Initialize node references
    m_tactics_participant   = godot::Object::cast_to<tog::TacticsParticipant>(get_node_or_null(tog::node::name::BattleTest::TacticsParticipant));
    m_tactics_player        = godot::Object::cast_to<tog::TacticsPlayer>(get_node_or_null(tog::node::name::BattleTest::TacticsPlayer));
    m_tactics_opponent      = godot::Object::cast_to<tog::TacticsOpponent>(get_node_or_null(tog::node::name::BattleTest::TacticsOpponent));
    m_tactics_arena         = godot::Object::cast_to<tog::TacticsArena>(get_node_or_null(tog::node::name::BattleTest::TacticsArena));

    if (not rl::engine::editor_active()) {
        //Configure arena tiles to be usable
        m_tactics_arena->configure_tiles();
        //Configures the TacticsParticipant's "TacticsParticipantService" with the shared tactics_camera and tactics_controls resource
        m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);
    }

    //Update camera boundary radius if necessary
    if (m_tactics_camera_resource->m_boundary_radius != m_camera_boundary_radius) {
        m_tactics_camera_resource->m_boundary_radius = m_camera_boundary_radius;
    }
    m_logger->log()->print("finished tog::TacticsLevel::_ready()");
}

void tog::TacticsLevel::_physics_process(double p_delta) {
    if (not rl::engine::editor_active()) {
        switch (m_turn_stage){
            case 0:
                //Checks whether both the player and opponent are configured via the participant subsystem
                init_turn();
                break;
            case 1:
                //Handle ongoing turn
                handle_turn(p_delta);
                break;
            default:
                break;
        }
    }
}

void tog::TacticsLevel::init_turn() {
    if ( m_tactics_participant->is_configured(m_tactics_player) && m_tactics_participant->is_configured(m_tactics_opponent) ) {
        //Move to turn handling stage if both player and opponent are configured
        m_turn_stage = 1;
    } else {
        //m_console->critical("pawn cannot start the turn");
    }
}

void tog::TacticsLevel::handle_turn(float delta) {
    m_logger->no_spam_log(tog::debug::Topic::PLAYER_CAN_ACT, m_tactics_participant->can_act(m_tactics_player));
    if (m_tactics_participant->can_act(m_tactics_player)) { //check if the player is acting

        if ( !m_tactics_participant->is_configured(m_tactics_player) ) {    //check if player is configured
            m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);   //configure the player
        }
        m_tactics_participant->act(delta, true, m_tactics_player);  //tactics_player takes it run

    } else if (m_tactics_participant->can_act(m_tactics_opponent)) { //check if the player is acting

        if ( !m_tactics_participant->is_configured(m_tactics_opponent) ) {  //check if opponent is configured
            m_tactics_participant->configure(m_tactics_camera_resource, m_tactics_controls_resource);   //configure the opponent
        }

        m_tactics_participant->act(delta, false, m_tactics_opponent);   //tactics_opponent takes it run

    } else {
        //reset the turn state
        m_tactics_player->reset_turn(m_tactics_player);
        m_tactics_opponent->reset_turn(m_tactics_opponent);
    }

}
