#pragma once

#include "stats.hpp"
#include "tactics_pawn_service.hpp"
#include "tactics_pawn_sprite.hpp"
#include "tactics_tile.hpp"

#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_pawn_resource.hpp"

#include "godot_cpp/classes/character_body3d.hpp"
#include "godot_cpp/core/class_db.hpp"


namespace tog {

    class TacticsPawnSprite;
    class TacticsPawnService;

    //Represents a pawn in the tactics game, handling movement, combat, and state management
    class TacticsPawn : public godot::CharacterBody3D {
        GDCLASS(TacticsPawn, godot::CharacterBody3D);

    public:
        TacticsPawn() = default;
        ~TacticsPawn() override = default;

        //Initializes the TacticsPawn node
        void _ready() override;

        //Processes pawn logic every physics frame
        //@param delta: Time elapsed since the last frame
        void _physics_process(double p_delta) override;

        //Centers the pawn on its current tile
        //@return: Whether the centering operation was successful
        bool center();

        //Shows or hides the pawn's stats UI
        //@param v: Whether to show (true) or hide (false) the stats
        void show_pawn_stats(bool v);

        //Gets the tile the pawn is currently on
        //@return: The TacticsTile the pawn is on
        tog::TacticsTile* get_tile() const;

        //Checks if the pawn is alive
        //@return: Whether the pawn's current health is above 0
        bool is_alive();

        //Checks if the pawn can move
        //@return: Whether the pawn can move and is alive
        bool can_pawn_move();

        //Checks if the pawn can attack
        //@return: Whether the pawn can attack and is alive
        bool can_pawn_attack();

        //Checks if the pawn can perform any action
        //@return: Whether the pawn can move or attack, and is alive
        bool can_act();

        //Resets the pawn's turn state
        void reset_turn();

        //Ends the pawn's turn
        void end_pawn_turn();

        //Initiates an attack on a target pawn
        //@param target_pawn: The TacticsPawn to attack
        //@param delta: Time elapsed since the last frame
        //@return: Whether the attack was successful
        bool attack_target_pawn(tog::TacticsPawn* target_pawn, float delta);

        //Moves the pawn along its designated path
        //@param delta: Time elapsed since the last frame
        void move_along_path(float delta);

    protected:
        static void _bind_methods() {};

    public:
        //Resource containing control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Resource containing pawn-specific data and configurations
        godot::Ref<tog::TacticsPawnResource> m_tactics_pawn_resource;
        //Service handling pawn-related logic and operations
        godot::Ref<tog::TacticsPawnService> m_tactics_pawn_service;
        //Reference to the Stats node, handling pawn statistics
        tog::Stats* m_stats_node;
        //The expertise (class or type) of the pawn
        godot::String m_expertise;
        //Reference to the TacticsPawnSprite node, handling visual representation
        tog::TacticsPawnSprite* m_tactics_pawn_sprite;
    };

}
