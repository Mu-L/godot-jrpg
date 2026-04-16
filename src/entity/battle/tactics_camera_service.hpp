#pragma once

#include "tactics_camera_movement_service.hpp"
#include "tactics_camera_panning_service.hpp"
#include "tactics_camera_rotation_service.hpp"
#include "tactics_camera_zoom_service.hpp"

#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/camera3d.hpp"

namespace tog {

    constexpr float MIN_VELOCITY = 0.01f;

    class TacticsCameraMovementService;
    class TacticsCameraZoomService;
    class TacticsCameraRotationService;
    class TacticsCameraPanningService;

    class TacticsCameraService : public godot::Object {
        GDCLASS(TacticsCameraService, godot::Object);

    public:
        static tog::TacticsCameraService* get();
        static tog::TacticsCameraService* reset();
        static tog::TacticsCameraService* reset(const godot::Ref<TacticsCameraResource>& camera_resource, const godot::Ref<TacticsControlsResource>& control_resource);
        static inline void cleanup();

        void setup(tog::TacticsCamera* tactics_camera, godot::Camera3D* camera);
        void process(float delta, tog::TacticsCamera* tactics_camera);

    private:
        TacticsCameraService() { m_static_inst = this; }
        TacticsCameraService(const godot::Ref<TacticsCameraResource>& camera_resource, const godot::Ref<TacticsControlsResource>& control_resource);
        ~TacticsCameraService() override { m_static_inst = nullptr; };

    protected:
        void static _bind_methods() {}

    public:
        godot::Ref<tog::TacticsCameraResource>          m_tactics_camera_resource;
        godot::Ref<tog::TacticsControlsResource>        m_tactics_control_resource;
        godot::Ref<TacticsCameraMovementService>        m_tactics_camera_movement_service;
        godot::Ref<tog::TacticsCameraZoomService>       m_tactics_zoom_service;
        godot::Ref<tog::TacticsCameraRotationService>   m_tactics_camera_rotation_service;
        godot::Ref<tog::TacticsCameraPanningService>    m_tactics_camera_panning_service;
    private:
        static inline tog::TacticsCameraService* m_static_inst = nullptr;

    };

}

