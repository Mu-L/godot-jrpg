#pragma once

#include "tactics_camera_movement_service.hpp"
#include "tactics_camera_panning_service.hpp"
#include "tactics_camera_rotation_service.hpp"
#include "tactics_camera_zoom_service.hpp"

#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_control_resource.hpp"

#include "godot_cpp/classes/object.hpp"

namespace tog {

    constexpr float MIN_VELOCITY = 0.01f;

    class TacticsCameraMovementService;
    class TacticsCameraZoomService;

    class TacticsCameraService : public godot::Object {
        GDCLASS(TacticsCameraService, godot::Object);

    public:
        static tog::TacticsCameraService* get();
        static inline tog::TacticsCameraService* reset();
        static inline tog::TacticsCameraService* reset(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource);
        static inline void cleanup() { delete m_static_inst; }

        TacticsCameraService() = default;
        TacticsCameraService(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource);
        ~TacticsCameraService() override = default;

    protected:
        void static _bind_methods() {}

    private:
        tog::TacticsCameraResource*         m_tactics_camera_resource = nullptr;
        tog::TacticsControlResource*        m_tactics_control_resource = nullptr;
        tog::TacticsCameraMovementService*  m_tactics_camera_movement_service = nullptr;
        tog::TacticsCameraZoomService*      m_tactics_zoom_service = nullptr;
        tog::TacticsCameraRotationService*  m_tactics_camera_rotation_service = nullptr;
        tog::TacticsCameraPanningService*   m_tactics_camera_panning_service = nullptr;
        static inline tog::TacticsCameraService* m_static_inst = nullptr;

    };

}

