#pragma once

#include "tactics_camera_service.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "singletons/console.hpp"

#include "godot_cpp/classes/character_body3d.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/classes/camera3d.hpp"


namespace tog {
    /*
     * Handles camera movement features
     * [code]rotate_camera[/code]: "Cardinal Points" mode [i](Q,E)[/i][br]
     * [code]move_camera[/code]: "Panning" mode [i](W,A,S,D)[/i][br]
     * [code]free_look[/code]: "Free Look" mode [i](MMB or Right Stick movement)[/i][br]
     * [code]follow[/code]: "Focus" mode [i](programmatically called)[/i][br][br]
     * Resource Interface: [TacticsCameraResource] -- Service: [TacticsCameraService]
     */

    class TacticsCameraResource;
    class TacticsCameraService;

    class TacticsCamera : public godot::CharacterBody3D {
        GDCLASS(TacticsCamera, godot::CharacterBody3D);

    public:

        TacticsCamera() = default;
        ~TacticsCamera() override = default;

        void _ready() override;
        //Process camera service
        void _process(double p_delta) override;

        //Moves the camera based on input
        void move_camera(float h, float v, bool joystick, float delta);
        //Rotates the camera
        void rotate_camera(float delta, int twist = 0);
        //Enables free look mode
        void free_look(float delta);
        //Zooms the camera
        static void zoom_camera(float zoom_increment);
        //Resets camera zoom to default
        void reset_cam_zoom();

    protected:
        static void _bind_methods() {}

    public:
        //Resource containing camera attributes and signals
        godot::Ref<tog::TacticsCameraResource>      m_tactics_camera_resource;
        //Resource containing control settings
        godot::Ref<tog::TacticsControlsResource>    m_tactics_control_resource;
        //Node for horizontal rotation - effectively yaw around the vertical axis
        godot::Node3D*                              m_t_pivot = nullptr;
        //Node for vertical rotation - the “look down/look up” part of the camera rig.
        godot::Node3D*                              m_p_pivot = nullptr;
        //Main camera node
        godot::Camera3D*                            m_camera = nullptr;
        //Service handling camera operations
        inline static tog::TacticsCameraService*    m_tactics_camera_service = nullptr; //holds reference to the static object that manages the service
        rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
    };

}
