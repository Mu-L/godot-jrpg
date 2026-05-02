#pragma once

#include "tactics_debug.hpp"
#include "tactics_pawn_movement_service.hpp"
#include "tactics_pawn_combat_service.hpp"
#include "tactics_pawn_animation_service.hpp"
#include "tactics_pawn_hud_service.hpp"
#include "tactics_pawn_sprite.hpp"
#include "tactics_pawn.hpp"

#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsPawnAnimationService;
    class TacticsPawnSprite;
    class TacticsPawnMovementService;
    class TacticsPawnHudService;
    class TacticsPawnCombatService;

    //Service class for managing pawn operations in the tactics game
    class TacticsPawnService : public godot::RefCounted {
        GDCLASS(TacticsPawnService, godot::RefCounted);

    public:
        //Initializes the TacticsPawnService and its sub-services
        TacticsPawnService();
        ~TacticsPawnService() override = default;

        //Sets up the pawn service, particularly the animation service
        //@param pawn: The TacticsPawn to set up
        void setup(tog::TacticsPawn* tactics_pawn);

        //Processes pawn-related operations every frame
        //@param pawn: The TacticsPawn to process
        //@param delta: Time elapsed since the last frame
        void process(tog::TacticsPawn* const tactics_pawn, float delta);

        //Initiates an attack on a target pawn
        //@param pawn: The attacking TacticsPawn
        //@param target_pawn: The TacticsPawn being attacked
        //@param delta: Time elapsed since the last frame
        //@return: Whether the attack was successful
        bool attack_target_pawn(tog::TacticsPawn* tactics_pawn, tog::TacticsPawn* target_tactics_pawn, float delta);

    protected:
        static void _bind_methods() {}

    public:
        tog::debug::Logger* m_logger{tog::debug::Logger::get()};
        //Service for handling pawn movement
        godot::Ref<tog::TacticsPawnMovementService> m_tactics_pawn_movement_service;
        //Service for handling pawn combat
        godot::Ref<tog::TacticsPawnCombatService> m_tactics_pawn_combat_service;
        //Service for handling pawn animations
        godot::Ref<tog::TacticsPawnAnimationService> m_tactics_pawn_animation_service;
        //Service for handling pawn HUD operations
        godot::Ref<tog::TacticsPawnHudService> m_tactics_pawn_hud_service;
        //Reference to the pawn's sprite
        tog::TacticsPawnSprite* m_tactics_pawn_sprite;
    };

}
