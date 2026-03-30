#pragma once

#include "tactics_controls.hpp"

#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/ref_counted.hpp"

namespace tog {

    class TacticsControlsResource;
    class TacticsControls;

    //Service class for managing UI-related functionalities in the Tactics game
    class TacticsUIService : public godot::RefCounted {
        GDCLASS(TacticsUIService, godot::RefCounted);

    public:
        TacticsUIService() = default;
        explicit TacticsUIService(const godot::Ref<tog::TacticsControlsResource>& controls_resource);
        ~TacticsUIService() override = default;

        //Updates the controller hints based on the current input device
        void update_controller_hints(tog::TacticsControls* tactics_controls);
        //Sets the visibility of the actions menu and updates action button states
        void set_actions_menu_visibility(bool v, tog::TacticsPawn* tactics_pawn, tog::TacticsControls* tactics_controls);

    protected:
        static void _bind_methods() {}

    private:
        //Reference to the TacticsControlsResource
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
    };

}
