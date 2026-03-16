#pragma once

#include "util/bind.hpp"
#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //Mapping
    //const godot::Array CAMERA_PAN_KEYS = {"camera_left", "camera_right", "camera_forward", "camera_backwards" };
    //The maximum length for the ray used in mouse cursor position casting
    inline static constexpr int RAY_LENGTH = 10000;
    //Deadzone for controller input to prevent unintended movement from small inputs
    inline static constexpr float CONTROLLER_DEADZONE = 0.05;
    //Sensitivity of right stick input
    inline static constexpr float RIGHT_STICK_SENSITIVITY = 1.0;

    //Stores input-related data and configurations
    //This resource class holds various input states and configurations used for input processing in the game.
    //It includes settings for both mouse and joystick input, as well as camera control parameters.
    class InputCaptureResource : public godot::Resource {
        GDCLASS(InputCaptureResource, godot::Resource);

    public:
        InputCaptureResource() = default;
        ~InputCaptureResource() override = default;

        void set_mouse_sensitivity(float value)     { m_mouse_sensitivity = value; }
        void set_camera_move_speed(float value)     { m_camera_move_speed = value; }
        void set_camera_rotate_speed(float value)   { m_camera_rotate_speed = value; }
        void set_camera_zoom_speed(float value)     { m_camera_zoom_speed = value; }

        float get_mouse_sensitivity(float value) const      { return m_mouse_sensitivity; }
        float get_camera_move_speed(float value) const      { return m_camera_move_speed; }
        float get_camera_rotate_speed(float value) const    { return m_camera_rotate_speed; }
        float get_camera_zoom_speed(float value) const      { return m_camera_zoom_speed; }

    protected:

        static void _bind_methods() {
            //bind property to editor
            rl::bind_property(InputCaptureResource, mouse_sensitivity, float);
            rl::bind_property(InputCaptureResource, camera_move_speed, float);
            rl::bind_property(InputCaptureResource, camera_rotate_speed, float);
            rl::bind_property(InputCaptureResource, camera_zoom_speed, float);
        }

    public:
        //Indicates whether joystick input is currently active
        inline static bool m_is_joystick = false;
        //Indicates whether free look input is currently active
        inline static bool m_free_look_pressed = false;

        //X-axis compound value of the right joystick
        inline static float m_right_stick_x{0.0f};
        //Y-axis compound value of the right joystick
        inline static float m_right_stick_y{0.0f};
        //X-axis compound value of the left joystick
        inline static float m_left_stick_x{0.0f};
        //Y-axis compound value of the left joystick
        inline static float m_left_stick_y{0.0f};

        //The current position of the joystick
        godot::Vector2 m_joystick_position = {0, 0 };
        //The current position of the mouse cursor
        godot::Vector2 m_mouse_position = { 0, 0 };

        //The current direction of the camera
        //inline static godot::Vector2 m_cam_direction = { 0, 0 };

        //The sensitivity of mouse input
        float m_mouse_sensitivity = 1.0f;
        //The speed at which the camera moves
        float m_camera_move_speed = 10.0f;
        //The speed at which the camera rotates
        float m_camera_rotate_speed = 5.0f;
        //The speed at which the camera zooms in and out
        float m_camera_zoom_speed = 1.0f;
    };

}

