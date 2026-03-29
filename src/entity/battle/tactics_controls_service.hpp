#pragma once

#include "tactics_controls_input_service.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "resources/battle/tactics_arena_resource.hpp"


namespace tog {

    class TacticsControlsInputService;

    //Service class for managing tactics controls and related functionalities
    class TacticsControlsService : public godot::RefCounted {
        GDCLASS(TacticsControlsService, godot::RefCounted);

    public:
        TacticsControlsService() = default;
        ~TacticsControlsService() override = default;

    protected:
        static void _bind_methods() {

        }

    private:
        //Reference to the TacticsControlsResource
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Reference to the TacticsCameraResource
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Reference to the TacticsParticipantResource
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Reference to the TacticsArenaResource
        godot::Ref<tog::TacticsArenaResource> m_tactics_arena_resource;
        //Node for capturing mouse clicks
        godot::Node* m_input_capture;
        //Service for handling input-related operations
        godot::Ref<tog::TacticsControlsInputService> m_tactics_controls_input_service;

    };

}
