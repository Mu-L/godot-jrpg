#pragma once

#include "tactics_camera.hpp"
#include "godot_cpp/classes/object.hpp"
#include "resources/battle/tactics_camera_resource.hpp"

namespace tog {

    class TacticsCamera;

    //Service class for handling camera panning in tactical view
    class TacticsCameraPanningService : public godot::Object {
        GDCLASS(TacticsCameraPanningService, godot::Object);

    public:
        TacticsCameraPanningService() = default;
        TacticsCameraPanningService(tog::TacticsCameraResource* tactics_camera) : m_tactics_camera_resource(tactics_camera) {};
        ~TacticsCameraPanningService() override = default;

        //Checks if the cursor is near the screen edge for edge panning
        bool is_cursor_near_edge(tog::TacticsCamera* tactics_camera);
        //Handles panning with WASD keys
        void wasd_pan(float delta, tog::TacticsCamera* tactics_camera, godot::Vector2 input_dir);
        //Handles panning when the cursor is near the screen edge
        void edge_pan(float delta, tog::TacticsCamera* tactics_camera);
        //Executes the panning movement
        bool do_pan(float h, float v, float delta, tog::TacticsCamera* tactics_camera);
        //Updates the viewport size if it has changed
        bool refresh_cam_viewpoint_size(tog::TacticsCamera* tactics_camera);
        //Calculates panning values based on mouse position
        godot::Dictionary get_mouse_panning_values();

    protected:
        void static _bind_methods() {}

    private:
        tog::TacticsCameraResource* m_tactics_camera_resource = nullptr;

    };

}

