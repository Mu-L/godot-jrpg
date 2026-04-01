#pragma once

#include <cstdint>
#include <string>


namespace tog::inline constants {

    namespace path {

        namespace scene {

            namespace ui {
                constexpr inline auto MainMenu          { "res://scenes/ui/main_menu.tscn" };
                constexpr inline auto CharacterCreator  { "res://scenes/ui/character_creator.tscn" };
                constexpr inline auto HomeScene         { "res://scenes/ui/home_scene.tscn" };
            }

        }

        namespace resource {

            namespace characters {
                constexpr inline auto dir_path  { "res://assets/resources/characters/" };
            }

            namespace player {
                constexpr inline auto main_player  { "res://assets/resources/player/main_player.tres" };
            }

            namespace battle {
                constexpr inline auto tactics_control_resource  { "res://assets/resources/battle/tactics_control_resource.tres" };
                constexpr inline auto tactics_tile_raycast      { "res://assets/resources/battle/tactics_tile_raycast.tres" };
            }

        }

    }

    namespace node {

        namespace signal {

            namespace BaseButton {
                constexpr inline auto pressed   { "pressed" };
            }

            namespace Control {
                constexpr inline auto gui_input   { "gui_input" };
            }

            namespace TacticsParticipantResource {
                constexpr inline auto called_skip_turn   { "called_skip_turn" };
            }

            namespace TacticsArenaResource {
                constexpr inline auto called_reset_all_tile_markers     { "called_reset_all_tile_markers" };
                constexpr inline auto called_get_pathfinding_tilestack  { "called_get_pathfinding_tilestack" };
                constexpr inline auto called_mark_hover_tile            { "called_mark_hover_tile" };
            }

            namespace TacticsControlResource {
                constexpr inline auto called_set_actions_menu_visibility   { "called_set_actions_menu_visibility" };
                constexpr inline auto called_move_camera                   { "called_move_camera" };
                constexpr inline auto called_select_pawn                   { "called_select_pawn" };
                constexpr inline auto called_select_pawn_to_attack         { "called_select_pawn_to_attack" };
                constexpr inline auto called_select_new_location           { "called_select_new_location" };
                constexpr inline auto called_set_cursor_shape_to_move      { "called_set_cursor_shape_to_move" };
                constexpr inline auto called_set_cursor_shape_to_arrow     { "called_set_cursor_shape_to_arrow" };
            }

            namespace TacticsPawnResource {
                constexpr inline auto pawn_moved    { "pawn_moved" };
                constexpr inline auto pawn_attacked { "pawn_attacked" };
                constexpr inline auto turn_ended    { "turn_ended" };
            }

            namespace TacticsCameraResource {
                constexpr inline auto called_move_camera    { "called_move_camera" };
                constexpr inline auto called_free_look      { "called_free_look" };
                constexpr inline auto called_rotate_camera  { "called_rotate_camera" };
            }

        }

        namespace name {

            namespace MainMenu {
                constexpr inline auto PlayButton    { "%PlayButton" };
                constexpr inline auto SettingsButton{ "%SettingsButton" };
                constexpr inline auto CreditButton  { "%CreditButton" };
                constexpr inline auto QuitButton    { "%QuitButton" };
            }

            namespace CharacterCreator {
                constexpr inline auto RoleContainer { "%RoleContainer" };
                constexpr inline auto StatsContainer{ "%StatsContainer" };
                constexpr inline auto CharNameLabel { "%CharNameLabel" };
                constexpr inline auto CharImage     { "%CharImage" };
                constexpr inline auto PrevCharButton{ "%PrevCharButton" };
                constexpr inline auto NextCharButton{ "%NextCharButton" };
                constexpr inline auto StartButton   { "%StartButton" };

                constexpr inline auto HealthValue   { "%HealthValue" };
                constexpr inline auto ShinsuValue   { "%ShinsuValue" };
                constexpr inline auto AttackValue   { "%AttackValue" };
                constexpr inline auto PowerValue    { "%PowerValue" };
                constexpr inline auto DefenseValue  { "%DefenseValue" };
                constexpr inline auto SpiritValue   { "%SpiritValue" };

            }

            namespace HomeScene {
                constexpr inline auto NameValue         { "%NameValue" };
                constexpr inline auto LevelValue        { "%LevelValue" };
                constexpr inline auto HPValue           { "%HPValue" };
                constexpr inline auto ShinsuValue       { "%ShinsuValue" };
                constexpr inline auto AttackValue       { "%AttackValue" };
                constexpr inline auto DefenseValue      { "%DefenseValue" };
                constexpr inline auto MagicPowerValue   { "%MagicPowerValue" };
                constexpr inline auto SpiritPowerValue  { "%SpiritPowerValue" };
                constexpr inline auto MainPlayer        { "%MainPlayer" };
                constexpr inline auto MainPlayerImage   { "%MainPlayerImage" };
            }

            namespace RayCasting {
                constexpr inline auto Neighbors { "Neighbors" };
                constexpr inline auto Above     { "Above" };
            }

            namespace BattleTest {
                constexpr inline auto TwistPivot    { "%TwistPivot" };
                constexpr inline auto PitchPivot    { "%TwistPivot/PitchPivot" };
                constexpr inline auto Camera3D      { "%TwistPivot/PitchPivot/Camera3D" };
                constexpr inline auto Stats         { "%Expertise/Stats" };
                constexpr inline auto AnimationTree { "%AnimationTree" };
                constexpr inline auto NameLabel     { "%CharacterUI/NameLabel" };
                constexpr inline auto Playback      { "Parameters/Playback" };
            }



        }

    }

    namespace signals {

    }


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace rl::inline constants {

    namespace name {

        namespace level {
            constexpr inline auto level1{ "Level1" };
            constexpr inline auto physics_box{ "PhysicsBox" };
        }

        namespace dialog {
            constexpr inline auto console{ "ConsolePanel" };
            constexpr inline auto canvas_layer{ "MainCanvasLayer" };
        }

        namespace main_menu {
            constexpr inline auto player{ "PlayButton" };
            constexpr inline auto settings{ "SettingsButton" };
            constexpr inline auto credit{ "CreditButton" };
            constexpr inline auto quit{ "QuitButton" };
        }

        namespace character {
            constexpr inline auto player{ "Player" };
            constexpr inline auto enemy{ "Enemy" };
            constexpr inline auto firing_pt{ "FiringPoint" };
        }

    }

    namespace event {
        constexpr inline auto position_changed{ "position_changed" };
        constexpr inline auto entered_area{ "entered_area" };
        constexpr inline auto exited_area{ "exited_area" };
        constexpr inline auto spawn_projectile{ "spawn_projectile" };
        constexpr inline auto character_move{ "character_move" };
        constexpr inline auto character_rotate{ "character_rotate" };
        constexpr inline auto character_shoot{ "character_shoot" };
        constexpr inline auto body_entered{ "body_entered" };
        constexpr inline auto body_exited{ "body_exited" };
        constexpr inline auto signal_example{ "custom_signal_example" };

        constexpr inline auto buttonPressed{ "pressed" };

        constexpr inline auto role_scroll{ "role_scroll" };
        constexpr inline auto gui_input{ "gui_input" };
        constexpr inline auto changeToPlayScene{ "change_to_play_scene" };
        constexpr inline auto quitGame{ "change_to_quit_scene" };
    }

    enum class LayerID : uint32_t {
        Player = 0x00000001,
        NPCs = 0x00000002,
        Projectiles = 0x00000004,
        Walls = 0x00000008,
        DamageZones = 0x00000010,
        DeathZones = 0x00000020,
        PhysicsObjects = 0x00000040,
        Layer08 = 0x00000080,
        Layer09 = 0x00000100,
        Layer10 = 0x00000200,
        Layer11 = 0x00000400,
        Layer12 = 0x00000800,
        Layer13 = 0x00001000,
        Layer14 = 0x00002000,
        Layer15 = 0x00004000,
        Layer16 = 0x00008000,
    };

    namespace path {

        namespace scene {
            constexpr inline auto Level1{ "res://scenes/levels/level1.tscn" };
            constexpr inline auto Player{ "res://scenes/characters/player.tscn" };
            constexpr inline auto Bullet{ "res://scenes/projectiles/bullet.tscn" };
        }

        namespace ui{
            constexpr inline auto MainDialog{ "res://scenes/ui/main_dialog.tscn" };
            constexpr inline auto MainMenu{ "res://scenes/ui/main_menu.tscn" };
            constexpr inline auto PlayScene{ "res://scenes/ui/play_scene.tscn" };
            constexpr inline auto HomeScene{ "res://scenes/ui/home_scene.tscn" };

        }

    }

}
