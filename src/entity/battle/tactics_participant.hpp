#pragma once

#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_controls_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"

#include "godot_cpp/classes/node3d.hpp"

namespace tog {

    //Handles participant (i.e. Player & Opponent) actions and decision-making
    //Resource Interface: [TacticsParticipantResource] -- Service: [TacticsParticipantService]
    //Parent of: [TacticsPlayer], [TacticsOpponent]

    class TacticsControlsResource;
    class TacticsParticipantResource;
    class TacticsCameraResource;
    class TacticsPlayer;

    class TacticsParticipant : public godot::Node3D {
        GDCLASS(TacticsParticipant, godot::Node3D);

    public:
        TacticsParticipant() = default;
        ~TacticsParticipant() override = default;

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Service handling participant logic and operations
        //godot::Ref<TacticsParticipantService>

    };

}
