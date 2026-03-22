#include "tactics_camera_movement_service.hpp"

tog::TacticsCameraMovementService::TacticsCameraMovementService(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource) {
    m_tactics_camera_resource = camera_resource;
    m_tactics_control_resource = control_resource;
}

void tog::TacticsCameraMovementService::move_camera(float h, float v, bool joystick, float delta, TacticsCamera*camera) {

    if (m_tactics_camera_resource->m_target || (h == 0 && v == 0)) {
        return;
    }

    //float angle = (godot::Math::atan2(-h,v))

}


