#pragma once

#include "resources/battle/tactics_controls_resource.hpp"

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/container.hpp"
#include "godot_cpp/classes/input_event.hpp"

namespace tog {

    constexpr float ANIMATION_DURATION = 0.3f;
    constexpr float FOLDED_OFFSET = -514.0f;

    //Controls the visibility and animation of controller hints
    //This script manages the folding and unfolding of controller hints
    //based on user input and mouse interactions.
    class InputHints : public godot::Container {
        GDCLASS(InputHints, godot::Container);

    public:

        InputHints() = default;
        ~InputHints() override = default;

        //Initializes the node and sets up signal connections
        void _ready() override;

        //Handles unhandled input events
        //@param event: The input event to handle
        void _unhandled_input(const godot::Ref<godot::InputEvent>& p_event) override;

        //Handles mouse enter event
        void on_mouse_entered();

        //Handles mouse exit event
        void on_mouse_exited();

        //Updates the visibility and position of the controller hints
        //@param force_immediate: Whether to update immediately without animation
        void update_hints_visibility(bool force_immediate = false);

    protected:
        static void _bind_methods() {}

    private:
        //Resource containing control-related data and configurations
        godot::Ref<tog::TacticsControlsResource> m_tactics_controls_resource;
        //Reference to the ControllerHints node
        godot::Control* m_controller_hints = nullptr;

    };

}
