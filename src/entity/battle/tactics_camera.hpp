#pragma once

#include "tactics_camera_service.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_control_resource.hpp"

#include "godot_cpp/classes/character_body3d.hpp"
#include "godot_cpp/core/class_db.hpp"


namespace tog {
    /*
     * Handles camera movement features
     * [code]rotate_camera[/code]: "Cardinal Points" mode [i](Q,E)[/i][br]
     * [code]move_camera[/code]: "Panning" mode [i](W,A,S,D)[/i][br]
     * [code]free_look[/code]: "Free Look" mode [i](MMB or Right Stick movement)[/i][br]
     * [code]follow[/code]: "Focus" mode [i](programmatically called)[/i][br][br]
     * Resource Interface: [TacticsCameraResource] -- Service: [TacticsCameraService]
     */
    class TacticsCamera : public godot::CharacterBody3D {
        GDCLASS(TacticsCamera, godot::CharacterBody3D);

    public:

        TacticsCamera();
        ~TacticsCamera() override = default;

        void _ready() override {};

    protected:

        static void _bind_methods() {

        }

    public:
        TacticsCameraResource* m_tactics_camera_resource = nullptr;
        TacticsControlResource* m_tactics_control_resource = nullptr;
        //inline static TacticsCameraService m_tactics_camera_service;
    };

}
