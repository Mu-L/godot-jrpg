#include "api/extension_interface.hpp"
#include <gdextension_interface.h>
#include "main.hpp"

#include "entity/battle/cursor_service.hpp"
#include "entity/battle/expertise.hpp"
#include "entity/battle/input_capture.hpp"
#include "entity/battle/input_capture_service.hpp"
#include "entity/battle/input_hints.hpp"
#include "entity/battle/stats.hpp"
#include "entity/battle/tactics_arena.hpp"
#include "entity/battle/tactics_arena_service.hpp"
#include "entity/battle/tactics_camera.hpp"
#include "entity/battle/tactics_camera_movement_service.hpp"
#include "entity/battle/tactics_camera_panning_service.hpp"
#include "entity/battle/tactics_camera_rotation_service.hpp"
#include "entity/battle/tactics_camera_service.hpp"
#include "entity/battle/tactics_camera_zoom_service.hpp"
#include "entity/battle/tactics_controls.hpp"
#include "entity/battle/tactics_controls_camera_service.hpp"
#include "entity/battle/tactics_controls_input_service.hpp"
#include "entity/battle/tactics_controls_selection_service.hpp"
#include "entity/battle/tactics_controls_service.hpp"
#include "entity/battle/tactics_debug.hpp"
#include "entity/battle/tactics_level.hpp"
#include "entity/battle/tactics_main.hpp"
#include "entity/battle/tactics_opponent.hpp"
#include "entity/battle/tactics_opponent_service.hpp"
#include "entity/battle/tactics_participant.hpp"
#include "entity/battle/tactics_participant_combat_service.hpp"
#include "entity/battle/tactics_participant_service.hpp"
#include "entity/battle/tactics_participant_turn_service.hpp"
#include "entity/battle/tactics_pawn.hpp"
#include "entity/battle/tactics_pawn_animation_service.hpp"
#include "entity/battle/tactics_pawn_combat_service.hpp"
#include "entity/battle/tactics_pawn_hud_service.hpp"
#include "entity/battle/tactics_pawn_movement_service.hpp"
#include "entity/battle/tactics_pawn_service.hpp"
#include "entity/battle/tactics_pawn_sprite.hpp"
#include "entity/battle/tactics_player.hpp"
#include "entity/battle/tactics_player_service.hpp"
#include "entity/battle/tactics_tile.hpp"
#include "entity/battle/tactics_tile_raycast.hpp"
#include "entity/battle/tactics_ui_service.hpp"

#include "entity/camera.hpp"
#include "entity/character/character.hpp"
#include "entity/character/enemy.hpp"
#include "entity/character/player.hpp"
#include "entity/controller/character_controller.hpp"
#include "entity/controller/enemy_controller.hpp"
#include "entity/controller/player_controller.hpp"
#include "entity/level.hpp"
#include "entity/projectile/projectile_spawner.hpp"

#include "resources/battle/input_capture_resource.hpp"
#include "resources/battle/stats_resource.hpp"
#include "resources/battle/tactics_arena_resource.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"
#include "resources/battle/tactics_pawn_resource.hpp"

#include "resources/character/character_portrait.hpp"
#include "resources/game/class_stats.hpp"
#include "resources/character/character_state.hpp"

#include "singletons/console.hpp"

#include "ui/class_selection.hpp"
#include "ui/main_dialog.hpp"
#include "ui/home_controller.hpp"

#include "util/engine.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <type_traits>



namespace rl {

    static inline console* console_singleton{ nullptr };
    static inline tog::debug::Logger* logger_singleton{ nullptr };

    void initialize_static_objects() {
        //register static object to be looked up as a singleton
        console_singleton = memnew(console);
        rl::engine::get()->register_singleton("Console", console::get());

        logger_singleton = memnew(tog::debug::Logger);
        rl::engine::get()->register_singleton("Logger", tog::debug::Logger::get());
    }

    void teardown_static_objects() {
        //delete the "TacticsCameraService" static object
        tog::TacticsCameraService::cleanup();

        rl::engine::get()->unregister_singleton("Logger");
        memdelete(logger_singleton);

        rl::engine::get()->unregister_singleton("Console");
        memdelete(console_singleton);
    }

    void initialize_extension_module(godot::ModuleInitializationLevel init_level) {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        godot::ClassDB::register_class<rl::Projectile>();
        godot::ClassDB::register_class<rl::ProjectileSpawner>();

        godot::ClassDB::register_abstract_class<rl::CharacterController>();
        godot::ClassDB::register_class<rl::PlayerController>(true);
        godot::ClassDB::register_class<rl::EnemyController>();

        godot::ClassDB::register_class<rl::Camera>();
        godot::ClassDB::register_class<rl::Character>();
        godot::ClassDB::register_class<rl::Enemy>();
        godot::ClassDB::register_class<rl::Player>();

        godot::ClassDB::register_class<rl::Level>();
        godot::ClassDB::register_class<rl::MainDialog>();

        //Main
        godot::ClassDB::register_class<rl::Main>();

        //UI Related
        godot::ClassDB::register_class<tog::ClassSelection>();
        godot::ClassDB::register_class<tog::HomeController>();

        //Util
        godot::ClassDB::register_class<console>();

        //Battle
        godot::ClassDB::register_class<tog::CursorService>();
        godot::ClassDB::register_class<tog::Expertise>();
        godot::ClassDB::register_class<tog::InputCapture>();
        godot::ClassDB::register_class<tog::InputCaptureService>();
        godot::ClassDB::register_class<tog::InputHints>();
        godot::ClassDB::register_class<tog::Stats>();
        godot::ClassDB::register_class<tog::TacticsArena>();
        godot::ClassDB::register_class<tog::TacticsArenaService>();
        godot::ClassDB::register_class<tog::TacticsCamera>();
        godot::ClassDB::register_class<tog::TacticsCameraMovementService>();
        godot::ClassDB::register_class<tog::TacticsCameraPanningService>();
        godot::ClassDB::register_class<tog::TacticsCameraRotationService>();
        godot::ClassDB::register_class<tog::TacticsCameraService>();
        godot::ClassDB::register_class<tog::TacticsCameraZoomService>();
        godot::ClassDB::register_class<tog::TacticsControls>();
        godot::ClassDB::register_class<tog::TacticsControlsCameraService>();
        godot::ClassDB::register_class<tog::TacticsControlsInputService>();
        godot::ClassDB::register_class<tog::TacticsControlsSelectionService>();
        godot::ClassDB::register_class<tog::TacticsControlsService>();
        godot::ClassDB::register_class<tog::debug::Logger>();
        godot::ClassDB::register_class<tog::TacticsLevel>();
        godot::ClassDB::register_class<tog::TacticsMain>();
        godot::ClassDB::register_class<tog::TacticsParticipant>();
        godot::ClassDB::register_class<tog::TacticsOpponent>();
        godot::ClassDB::register_class<tog::TacticsOpponentService>();
        godot::ClassDB::register_class<tog::TacticsParticipantCombatService>();
        godot::ClassDB::register_class<tog::TacticsParticipantService>();
        godot::ClassDB::register_class<tog::TacticsParticipantTurnService>();
        godot::ClassDB::register_class<tog::TacticsPawn>();
        godot::ClassDB::register_class<tog::TacticsPawnAnimationService>();
        godot::ClassDB::register_class<tog::TacticsPawnCombatService>();
        godot::ClassDB::register_class<tog::TacticsPawnHudService>();
        godot::ClassDB::register_class<tog::TacticsPawnMovementService>();
        godot::ClassDB::register_class<tog::TacticsPawnService>();
        godot::ClassDB::register_class<tog::TacticsPawnSprite>();
        godot::ClassDB::register_class<tog::TacticsPlayer>();
        godot::ClassDB::register_class<tog::TacticsPlayerService>();
        godot::ClassDB::register_class<tog::TacticsTile>();
        godot::ClassDB::register_class<tog::TacticsTileRaycast>();
        godot::ClassDB::register_class<tog::TacticsUIService>();

        //Resources
        //battle
        godot::ClassDB::register_class<tog::InputCaptureResource>();
        godot::ClassDB::register_class<tog::StatsResource>();
        godot::ClassDB::register_class<tog::TacticsArenaResource>();
        godot::ClassDB::register_class<tog::TacticsCameraResource>();
        godot::ClassDB::register_class<tog::TacticsControlsResource>();
        godot::ClassDB::register_class<tog::TacticsParticipantResource>();
        godot::ClassDB::register_class<tog::TacticsPawnResource>();

        //game
        godot::ClassDB::register_class<tog::ClassStats>();
        //character
        godot::ClassDB::register_class<tog::CharacterPortraitSheet>();
        godot::ClassDB::register_class<tog::CharacterState>();

        initialize_static_objects();
    }

    void uninitialize_extension_module(godot::ModuleInitializationLevel init_level) {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        teardown_static_objects();
    }

    extern "C"
    {
        GDExtensionBool GDE_EXPORT extension_library_init(GDExtensionInterfaceGetProcAddress addr,
                                                          GDExtensionClassLibraryPtr lib,
                                                          GDExtensionInitialization* init) {
            const auto init_level = godot::MODULE_INITIALIZATION_LEVEL_SCENE;
            godot::GDExtensionBinding::InitObject init_obj(addr, lib, init);

            init_obj.register_initializer(initialize_extension_module);
            init_obj.register_terminator(uninitialize_extension_module);
            init_obj.set_minimum_library_initialization_level(init_level);

            return init_obj.init();
        }
    }
}
