#pragma once

#include "tactics_camera.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/object.hpp"

namespace tog {

    class TacticsCamera;

    //Service class for handling camera rotation in tactical view
    class TacticsCameraRotationService : public godot::RefCounted {
        GDCLASS(TacticsCameraRotationService, godot::RefCounted);

    public:
        TacticsCameraRotationService() = default;
        TacticsCameraRotationService(const godot::Ref<tog::TacticsCameraResource>& camera_resource, const godot::Ref<tog::TacticsControlsResource>& control_resource);
        ~TacticsCameraRotationService() override = default;

        //Handles free look camera rotation
        void free_look(float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot);
        //Rotates the camera to the target rotation
        void rotate_camera(float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot);
        //Checks and handles free look activation based on input type
        void check_free_look_activation(float delta, tog::TacticsCamera* tactics_camera);
        //Deactivates free look mode
        void deactivate_free_look(tog::TacticsCamera* tactics_camera);
        //Updates the free look timer and deactivates if timeout is reached
        void update_free_look_timer(float delta, tog::TacticsCamera* tactics_camera);
        //Adds an angle to the horizontal rotation
        void add_angle_to_horizontal_rotation(int twist);
        //Gets the input for free look based on control type
        godot::Vector2 get_free_look_input();
        //Gets joystick input for free look
        godot::Vector2 get_free_look_joystick_input();
        //Gets mouse input for free look
        godot::Vector2 get_free_look_mouse_input();
        //Applies free look rotation to the camera pivots
        void apply_free_look_rotation(godot::Vector2 input, float delta, godot::Node3D* t_pivot, godot::Node3D* p_pivot);
        //Resets twist and pitch inputs
        void reset_twist_pitch_inputs();
        //Checks if joystick input is active
        bool is_joystick_input_active();
        //Snaps the camera to the nearest quadrant when free look is deactivated
        void snap_to_nearest_quadrant(tog::TacticsCamera* tactics_camera);
        //Calculates the nearest quadrant for camera snapping
        godot::Vector3 calculate_nearest_quadrant(tog::TacticsCamera* tactics_camera);

    private:
        //Ensure final rotation is within 0-360 range
        void on_tween_cb(tog::TacticsCamera* tactics_camera);

    protected:
        void static _bind_methods() {}

    private:
        const int m_DELTA_SMOOTHING = 10;
        const int m_MAX_VERT_ROT = 20;
        const int m_MIN_VERT_ROT = 20;
        const int m_FREE_LOOK_ROT_FACTOR = 20;

        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        godot::Ref<tog::TacticsControlsResource> m_tactics_control_resource;
    };

}

