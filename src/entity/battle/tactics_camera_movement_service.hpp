#pragma once

#include "tactics_camera.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_control_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    inline static constexpr int DELTA_SMOOTHING = 8;
    inline static constexpr int FAST_SMOOTHING = 100;
    inline static constexpr int VELOCITY_SMOOTHING = 8;
    inline static constexpr float MIN_THRESHOLD = 0.1;
    inline static constexpr float MIN_DISTANCE = 0.25;
    inline static constexpr int SPEED_DIVIDER = 4;

    //Service class for handling camera movement in tactical view
    class TacticsCameraMovementService : public godot::RefCounted {
        GDCLASS(TacticsCameraMovementService, godot::RefCounted);

    public:
        TacticsCameraMovementService() = default;
        TacticsCameraMovementService(TacticsCameraResource* camera_resource, TacticsControlResource* control_resource);
        ~TacticsCameraMovementService() override = default;

        void move_camera(float h, float v, bool joystick, float delta, TacticsCamera* camera);

    protected:
        void static _bind_methods() {

        }

    private:
        TacticsCameraResource* m_tactics_camera_resource = nullptr;
        TacticsControlResource* m_tactics_control_resource = nullptr;
    };

}

