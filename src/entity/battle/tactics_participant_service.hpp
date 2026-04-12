#include "resources/battle/tactics_participant_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"
#include "resources/battle/tactics_camera_resource.hpp"

namespace tog {

    //Service class for TacticsParticipant
    //Dependency of: [TacticsParticipant]
    class TacticsParticipantService : public godot::RefCounted {
        GDCLASS(TacticsParticipantService, godot::RefCounted);

    public:
        TacticsParticipantService() = default;
        ~TacticsParticipantService() override = default;

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing participant data and configurations
        godot::Ref<tog::TacticsParticipantResource> m_tactics_participant_resource;
        //Resource for camera-related data and configurations
        godot::Ref<tog::TacticsCameraResource> m_tactics_camera_resource;
        //Resource for control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Service handling turn-related logic
        //godot::Ref<tog::TacticsPart

    };

}
