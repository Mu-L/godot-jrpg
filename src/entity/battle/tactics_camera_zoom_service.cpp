#include "tactics_camera_zoom_service.hpp"

#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/tween.hpp"
#include "godot_cpp/core/math.hpp"

void tog::TacticsCameraZoomService::zoom_camera(float zoom_inc) const {
    m_tactics_camera_resource->m_target_fov = godot::Math::clamp(m_tactics_camera_resource->m_target_fov + zoom_inc,
                                                            m_tactics_camera_resource->m_min_zoom,
                                                            m_tactics_camera_resource->m_max_zoom);
}

void tog::TacticsCameraZoomService::apply_zoom_smoothing(tog::TacticsCamera* camera, float delta) const {
    if (m_tactics_camera_resource->m_current_fov != m_tactics_camera_resource->m_target_fov) {
        m_tactics_camera_resource->m_current_fov = godot::Math::lerp(   m_tactics_camera_resource->m_current_fov,
                                                                        m_tactics_camera_resource->m_target_fov,
                                                                        (m_tactics_camera_resource->m_zoom_smoothness * m_DELTA_SMOOTHING) * delta);
        camera->m_camera->set_fov(m_tactics_camera_resource->m_current_fov);
    }
}

void tog::TacticsCameraZoomService::reset_camera_zoom(tog::TacticsCamera* camera, godot::Camera3D* camera_node) const {
    m_tactics_camera_resource->m_target_fov = 30;
    const auto tween = camera->create_tween();
    tween->tween_property(camera_node, "fov", m_tactics_camera_resource->m_target_fov, m_tactics_camera_resource->m_zoom_duration)->set_trans(godot::Tween::TRANS_SINE);
}

