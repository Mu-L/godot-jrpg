#include "tactics_camera_service.hpp"

tog::TacticsCameraService * tog::TacticsCameraService::get() { return m_static_inst; }

tog::TacticsCameraService * tog::TacticsCameraService::reset() {
    delete m_static_inst;
    m_static_inst = memnew(TacticsCameraService);
    return m_static_inst;
}

tog::TacticsCameraService * tog::TacticsCameraService::reset(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource) {
    delete m_static_inst;
    m_static_inst = memnew(TacticsCameraService(camera_resource, control_resource));
    return m_static_inst;
}

tog::TacticsCameraService::TacticsCameraService(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource) {
    //point the static ptr to the current initialized object
    m_static_inst = this;
    //set the resources
    m_tactics_camera_resource = camera_resource;
    m_tactics_control_resource = control_resource;
    //initialize the "Tactics Camera Movement" sub-system
    m_tactics_camera_movement_service = memnew(TacticsCameraMovementService(camera_resource, control_resource));
}
