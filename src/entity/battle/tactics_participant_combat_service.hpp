#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "resources/battle/tactics_camera_resource.hpp"
#include "resources/battle/tactics_participant_resource.hpp"

namespace tog {

    //Service class for handling combat-related actions
    //Parent: [TacticsParticipantService]
    class TacticsParticipantCombatService : public godot::RefCounted {
        GDCLASS(TacticsParticipantCombatService, godot::RefCounted);

    public:
        TacticsParticipantCombatService() = default;
        TacticsParticipantCombatService(
            const godot::Ref<tog::TacticsParticipantResource>& participant_resource,
            const godot::Ref<tog::TacticsCameraResource>& camera_resource,
            const godot::Ref<tog::TacticsControlsResource>& controls_resource
            ) : m_tactics_participant_resource{participant_resource},
                m_tactics_camera_resource{camera_resource},
                m_tactics_controls_resource{controls_resource} {};
        ~TacticsParticipantCombatService() override = default;

        //Handles the attack action of a pawn
        //@param delta: Time elapsed since the last frame
        //@param is_player: Whether the attacking pawn belongs to the player
        void attack_pawn( float delta, bool is_player );

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;

    };

}

