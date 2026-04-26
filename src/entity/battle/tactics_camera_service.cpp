#include "tactics_camera_service.hpp"

#include "godot_cpp/classes/viewport.hpp"
#include "resources/battle/input_capture_resource.hpp"
#include "util/utility_vec.hpp"

tog::TacticsCameraService* tog::TacticsCameraService::get() { return m_static_inst; }

tog::TacticsCameraService* tog::TacticsCameraService::reset() {
    rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
    m_console->print("called tog::TacticsCameraService::reset()");
    cleanup();
    m_static_inst = memnew(TacticsCameraService);
    return m_static_inst;
}

tog::TacticsCameraService* tog::TacticsCameraService::reset(const godot::Ref<TacticsCameraResource>& camera_resource, const godot::Ref<TacticsControlsResource>& control_resource) {
    rl::Console<godot::RichTextLabel>* m_console{rl::console::get() };
    m_console->print("called tog::TacticsCameraService::reset(camera_resource, control_resource)");
    cleanup();
    m_static_inst = memnew(TacticsCameraService(camera_resource, control_resource));
    return m_static_inst;
}

void tog::TacticsCameraService::cleanup() {
    if (m_static_inst) {
        godot::memdelete(m_static_inst);
        m_static_inst = nullptr;
    }
}

void tog::TacticsCameraService::setup(tog::TacticsCamera* tactics_camera, godot::Camera3D* camera) {
    m_console->print("called tog::TacticsCameraService::setup()");
    if (m_tactics_camera_resource.is_null()) {
        assertion(false, "TacticsCamera needs a CameraResource (T Cam)");
    } else if (m_tactics_control_resource.is_null()) {
        assertion(false, "TacticsControls needs a ControlResource");
    } else {
        m_tactics_camera_resource->m_target_fov = camera->get_fov();
        m_tactics_camera_resource->m_viewport_size = tactics_camera->get_viewport()->get_visible_rect().size;
    }
}

void tog::TacticsCameraService::process(float delta, tog::TacticsCamera* tactics_camera) {
    m_tactics_camera_rotation_service->check_free_look_activation(delta, tactics_camera);
    if ( m_tactics_camera_resource->m_in_free_look ) {
        m_tactics_camera_rotation_service->free_look(delta, tactics_camera->m_t_pivot, tactics_camera->m_p_pivot);
    } else if ( !m_tactics_camera_resource->m_is_snapping_to_quad ) {
        m_tactics_camera_rotation_service->rotate_camera(delta, tactics_camera->m_t_pivot, tactics_camera->m_p_pivot);
    }

    godot::Vector2 input_dir = tog::InputCaptureResource::m_cam_direction;
    if ( input_dir != godot::Vector2(0,0) ) {
        m_tactics_camera_panning_service->wasd_pan(delta, tactics_camera, input_dir);
    } else if ( m_tactics_camera_panning_service->is_cursor_near_edge(tactics_camera) && (!m_tactics_control_resource->m_is_joystick) ) {
        m_tactics_camera_panning_service->edge_pan(delta, tactics_camera);
    } else {
        m_tactics_camera_resource->m_panning_timer = 0.0f;
        m_tactics_camera_movement_service->stabilize_camera(delta, tactics_camera);
    }

    if ( tactics_camera->get_velocity().length() < tog::MIN_VELOCITY ) {
        tactics_camera->set_velocity(get_zero_vector3());
    }

    m_tactics_camera_movement_service->focus_on_target(tactics_camera);
    m_tactics_zoom_service->apply_zoom_smoothing(tactics_camera, delta);
}

tog::TacticsCameraService::TacticsCameraService(const godot::Ref<TacticsCameraResource>& camera_resource, const godot::Ref<TacticsControlsResource>& control_resource) {
    //point the static ptr to the current initialized object
    m_static_inst = this;
    //set the resources
    m_tactics_camera_resource = camera_resource;
    m_tactics_control_resource = control_resource;
    //initialize the "Tactics Camera Movement" sub-system
    m_tactics_camera_movement_service   = memnew(TacticsCameraMovementService(camera_resource, control_resource));
    m_tactics_zoom_service              = memnew(TacticsCameraZoomService(camera_resource));
    m_tactics_camera_rotation_service   = memnew(TacticsCameraRotationService(camera_resource, control_resource));
    m_tactics_camera_panning_service    = memnew(TacticsCameraPanningService(camera_resource));
}
