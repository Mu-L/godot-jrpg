#include "tactics_camera_panning_service.hpp"

#include "godot_cpp/classes/viewport.hpp"

bool tog::TacticsCameraPanningService::is_cursor_near_edge(tog::TacticsCamera* tactics_camera) {
    refresh_cam_viewpoint_size(tactics_camera);
    m_tactics_camera_resource->m_mouse_position = tactics_camera->get_viewport()->get_mouse_position();
    auto panning = get_mouse_panning_values();
    return (static_cast<float>(panning["h"]) != 0) || (static_cast<float>(panning["v"]) != 0);
}

void tog::TacticsCameraPanningService::wasd_pan(float delta, tog::TacticsCamera* tactics_camera, godot::Vector2 input_dir) {
    float h_value = static_cast<float>(input_dir.x);
    float v_value = static_cast<float>(-input_dir.y);
    do_pan(h_value, v_value, delta, tactics_camera);
}

void tog::TacticsCameraPanningService::edge_pan(float delta, tog::TacticsCamera* tactics_camera) {
    refresh_cam_viewpoint_size(tactics_camera);
    auto panning = get_mouse_panning_values();
    float h_value = panning["h"];
    float v_value = panning["v"];
    do_pan(h_value, v_value, delta, tactics_camera);
}

bool tog::TacticsCameraPanningService::do_pan(float h, float v, float delta, tog::TacticsCamera* tactics_camera) {
    if (h != 0 || v != 0) {
        m_tactics_camera_resource->m_panning_timer += delta;
        if (m_tactics_camera_resource->m_panning_timer >= PANNING_DELAY) {
            tactics_camera->move_camera(h, v, false, delta);
            return true;
        }
    } else {
        m_tactics_camera_resource->m_panning_timer = 0.0f;
    }
    return false;
}

bool tog::TacticsCameraPanningService::refresh_cam_viewpoint_size(tog::TacticsCamera* tactics_camera) {
    godot::Vector2i new_viewpoint_size = tactics_camera->get_viewport()->get_visible_rect().get_size();
    if (new_viewpoint_size != m_tactics_camera_resource->m_viewport_size) {
        m_tactics_camera_resource->m_viewport_size = new_viewpoint_size;
        return true;
    } else {
        return false;
    }
}

godot::Dictionary tog::TacticsCameraPanningService::get_mouse_panning_values() {
    //return result
    godot::Dictionary result;

    float h = 0.0f;
    float v = 0.0f;

    if ( m_tactics_camera_resource->m_mouse_position.x <= m_tactics_camera_resource->m_border_pan_px_threshold ) {
        h = -1.0f;
    } else if ( m_tactics_camera_resource->m_mouse_position.x >= m_tactics_camera_resource->m_viewport_size.x - m_tactics_camera_resource->m_border_pan_px_threshold) {
        h = 1.0f;
    }

    if ( m_tactics_camera_resource->m_mouse_position.y <= m_tactics_camera_resource->m_border_pan_px_threshold ) {
        v = 1.0f;
    } else if ( m_tactics_camera_resource->m_mouse_position.y >= m_tactics_camera_resource->m_viewport_size.y - m_tactics_camera_resource->m_border_pan_px_threshold) {
        v = -1.0f;
    }

    result["h"] = h;
    result["v"] = v;

    return result;
}