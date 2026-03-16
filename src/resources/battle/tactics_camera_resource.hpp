#pragma once

#include "core/constants.hpp"
#include "util/bind.hpp"

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/resource.hpp"


namespace tog {

    //Delay before panning starts
    inline static constexpr float PANNING_DELAY = 0.95f;
    //Timeout for free look mode
    inline static constexpr float FREE_LOOK_TIMEOUT = 0.05;

    class TacticsCameraResource : public godot::Resource {
        GDCLASS(TacticsCameraResource, godot::Resource);
    public:

        TacticsCameraResource() = default;
        ~TacticsCameraResource() override = default;


        void move_camera(float h, float v, bool joystick, float delta);
        void rotate_camera(float delta, float twist = 0.0f);
        void free_look(float delta);

    protected:

        static void _bind_methods() {
            //Emitted when camera movement is requested
            rl::signal_binding<TacticsCameraResource, tog::node::signal::TacticsCameraResource::called_move_camera>::add<float, float, bool, float>();
            //Emitted when free look is activated
            rl::signal_binding<TacticsCameraResource, tog::node::signal::TacticsCameraResource::called_free_look>::add<float, float>();
            //Emitted when camera rotation is requested
            rl::signal_binding<TacticsCameraResource, tog::node::signal::TacticsCameraResource::called_rotate_camera>::add<float>();
        }

    public:
        //MOVEMENT
        //Movement speed of the camera
        int m_move_speed;
        //Rotation speed of the camera
        inline static float m_rot_speed = 10/10.f;
        //Smoothing factor for camera movement
        float m_smoothing = 0.1f;
        //Target velocity for camera movement
        godot::Vector3 m_target_velocity = { 0, 0, 0 };
        //Target node for camera to focus on
        godot::Node3D* m_target = nullptr;

        //ZOOM
        //Speed of camera zoom
        inline static float m_zoom_speed = 0.5f;
        //Smoothness of zoom transition
        float m_zoom_smoothness = 0.1f;
        //Duration of zoom transition
        float m_zoom_duration = 0.5f;
        //Minimum zoom level (closest)
        float m_min_zoom = 1.0f;
        //Maximum zoom level (farthest)
        float m_max_zoom = 10.0f;
        //Current Field of View
        float m_current_fov = 50.0f;
        //Target Field of View for smooth transition
        float m_target_fov = 50.0f;

        //PANNING
        //Radius of the boundary for camera movement
        float m_boundary_radius = 10.0f;
        //Center point of the boundary
        godot::Vector3 m_boundry_center = { 0, 0, 0 };
        //Threshold for edge panning in pixels
        float m_border_pan_px_threshold = 1.0f;
        //Speed of mouse-controlled panning
        float m_mouse_pan_speed = 0.5f;
        //Speed of joystick-controlled panning
        float m_joy_pan_speed = 0.5f;
        //Timer to track panning delay
        float m_panning_timer = 0.0f;

        //ROTATION
        //Duration of snapping to nearest quardrant
        float m_quad_snap_duration = 0.2f;
        //Flag to indicate if camera is snapping to quadrant
        bool m_is_snapping_to_quad = false;
        //Flag to indicate if camera is rotating
        inline static bool m_is_rotating = false;
        //Vertical pitch rotation
        inline static int m_x_rotation = 0;
        //Horizontal twist rotation
        inline static int m_y_rotation = 0;
        //Roll rotation
        inline static int m_z_rotation = 0;
        //Current mouse position
        godot::Vector2 m_mouse_position;
        //Flag to indicate if camera is in free look mode
        inline static bool m_in_free_look;
        //Timer for free look mode
        float m_free_look_timer = 0.0f;
        //Input for twisting rotation
        inline static float m_twist_input = 0;
        //Input for pitch rotation
        inline static float m_pitch_input = 0;
        //Size of the viewport
        godot::Vector2i m_viewport_size;

    };

}


