#include "api/extension_interface.hpp"
#include <gdextension_interface.h>
#include "main.hpp"

#include "entity/battle/input_capture.hpp"
#include "entity/battle/input_capture_service.hpp"
#include "entity/battle/tactics_camera.hpp"
#include "entity/battle/tactics_camera_movement_service.hpp"
#include "entity/battle/tactics_camera_panning_service.hpp"
#include "entity/battle/tactics_camera_rotation_service.hpp"
#include "entity/battle/tactics_camera_service.hpp"
#include "entity/battle/tactics_camera_zoom_service.hpp"
#include "entity/battle/tactics_controls.hpp"
#include "entity/battle/tactics_participant.hpp"
#include "entity/battle/tactics_pawn.hpp"
#include "entity/battle/tactics_player.hpp"
#include "entity/battle/tactics_tile.hpp"
#include "entity/battle/tactics_tile_raycast.hpp"

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

    void initialize_static_objects() {
        //register static object to be looked up as a singleton
        console_singleton = memnew(console);
        rl::engine::get()->register_singleton("Console", console::get());
    }

    void teardown_static_objects() {
        rl::engine::get()->unregister_singleton("Console");
        memdelete(console_singleton);

        //delete the "TacticsCameraService" static object
       tog::TacticsCameraService::cleanup();
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
        godot::ClassDB::register_class<tog::InputCapture>();
        godot::ClassDB::register_class<tog::InputCaptureService>();
        godot::ClassDB::register_class<tog::TacticsCamera>();
        godot::ClassDB::register_class<tog::TacticsCameraMovementService>();
        godot::ClassDB::register_class<tog::TacticsCameraPanningService>();
        godot::ClassDB::register_class<tog::TacticsCameraRotationService>();
        godot::ClassDB::register_class<tog::TacticsCameraService>();
        godot::ClassDB::register_class<tog::TacticsCameraZoomService>();
        godot::ClassDB::register_class<tog::TacticsControls>();
        godot::ClassDB::register_class<tog::TacticsParticipant>();
        godot::ClassDB::register_class<tog::TacticsPawn>();
        godot::ClassDB::register_class<tog::TacticsPlayer>();
        //godot::ClassDB::register_class<tog::TacticsTile>();
        godot::ClassDB::register_class<tog::TacticsTileRaycast>();

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
