#pragma once

#include "godot_cpp/classes/object.hpp"
#include "resources/battle/tactics_camera_resource.hpp"

namespace tog {


    //Service class for managing camera controls in the Tactics game.
    class TacticsControlsCameraService : public godot::RefCounted {
        GDCLASS(TacticsControlsCameraService, godot::RefCounted);

    public:
        TacticsControlsCameraService() = default;
        //Initializes the TacticsControlsCameraService with the necessary camera resource
        explicit TacticsControlsCameraService(const godot::Ref<tog::TacticsCameraResource>& camera_resource) : m_tactics_camera_resource{camera_resource} {};
        ~TacticsControlsCameraService() override = default;

        //Handles camera movement based on input
        //The movement is determined by the input strengths for left, right, forward, and backward actions
        void move_camera(float delta, bool is_joystick);

    protected:
        static void _bind_methods() {}

    private:
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;

    };

}
