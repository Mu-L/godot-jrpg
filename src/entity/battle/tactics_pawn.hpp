#pragma once

#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_pawn_resource.hpp"

#include "godot_cpp/classes/character_body3d.hpp"
#include <godot_cpp/core/class_db.hpp>

#include "stats.hpp"
#include "tactics_pawn_service.hpp"


namespace tog {

    //Represents a pawn in the tactics game, handling movement, combat, and state management
    class TacticsPawn : public godot::CharacterBody3D {
        GDCLASS(TacticsPawn, godot::CharacterBody3D);

    public:

        TacticsPawn() = default;
        ~TacticsPawn() override = default;

        void _ready() override {};

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing pawn-specific data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Resource containing pawn-specific data and configurations
        godot::Ref<tog::TacticsPawnResource> m_tactics_pawn_resource;
        //Service handling pawn-related logic and operations
        godot::Ref<tog::TacticsPawnService> m_tactics_pawn_service;
        //Reference to the Stats node, handling pawn statistics
        tog::Stats* m_stats_node;
        //The expertise (class or type) of the pawn
        godot::String m_expertise;
        //tog::TacticsPawnSprite
    };

}
