#pragma once

#include "entity/battle/tactics_camera.hpp"
#include "resources/battle/tactics_camera_resource.hpp"

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/camera3d.hpp"

namespace tog {

    class TacticsCamera;

    //Service class for handling camera zoom in tactical view
    class TacticsCameraZoomService : public godot::RefCounted {
        GDCLASS(TacticsCameraZoomService, godot::RefCounted);

    public:
        TacticsCameraZoomService() = default;
        explicit TacticsCameraZoomService(const godot::Ref<tog::TacticsCameraResource>& camera_resource) { m_tactics_camera_resource = camera_resource; }
        ~TacticsCameraZoomService() override = default;

        //Adjust the target FOV for zooming
        void zoom_camera(float zoom_inc) const;
        //Smoothly interpolate current FOV to target FOV
        void apply_zoom_smoothing(tog::TacticsCamera* camera, float delta) const;
        //Reset camera zoom to default value
        void reset_camera_zoom(tog::TacticsCamera* camera, godot::Camera3D* camera_node) const;

    protected:
        void static _bind_methods() {}

    private:
        const int m_DELTA_SMOOTHING = 10;
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
    };

}

