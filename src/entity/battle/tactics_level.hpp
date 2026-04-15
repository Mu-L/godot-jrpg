#pragma once

#include "godot_cpp/classes/node3d.hpp"

namespace tog {
    class TacticsArena;
    class TacticsOpponent;
    class TacticsPlayer;
    class TacticsParticipant;

    class TacticsControlsResource;
    class TacticsCameraResource;

    //Tactics system initialization & turn_stage management.
    //This is the Tactics Level's topmost script
    //Dependencies: [TacticsArena], [TacticsTile], [TacticsCamera], [TacticsControls], [TacticsParticipant], [TacticsOpponent], [TacticsPlayer], [TacticsPawn]
    class TacticsLevel : public godot::Node3D {
        GDCLASS(TacticsLevel, godot::Node3D);

    public:
        TacticsLevel() = default;
        ~TacticsLevel() override = default;

        void _ready() override;

        void _physics_process(double p_delta) override;

        //Checks requirements to begin the first turn.[br]Used by [TacticsPlayer], [TacticsOpponent]
        void init_turn();

        //Turn state management.[br]Used by [TacticsPlayer], [TacticsOpponent]
        void handle_turn(float delta);

    protected:
        void static _bind_methods() {};

    private:
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        float m_camera_boundary_radius = 10.0f;
        tog::TacticsParticipant* m_tactics_participant;
        tog::TacticsPlayer* m_tactics_player;
        tog::TacticsOpponent* m_tactics_opponent;
        tog::TacticsArena* m_tactics_arena;
        int m_turn_stage = 0;

    };

}


