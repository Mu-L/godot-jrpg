#pragma once

#include "tactics_control.hpp"

#include "resources/battle/tactics_control_resource.hpp"

#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/input.hpp"

namespace tog {

    //Service class for managing input-related functionalities in the Tactics game
    class TacticsControlsInputService : public godot::RefCounted {
        GDCLASS(TacticsControlsInputService, godot::RefCounted);

    public:
        TacticsControlsInputService() = default;
        //Initializes the TacticsControlsInputService with necessary resources and nodes
        TacticsControlsInputService(godot::Ref<tog::TacticsControlResource> controls, godot::Node* input_capture);
        ~TacticsControlsInputService() override = default;

        //Updates the mouse mode based on whether a joystick is being used
        void update_mouse_mode();
        //Handles input events and updates the joystick status
        void handle_input(const godot::Ref<godot::InputEvent>& event);
        //Gets the 3D position of the mouse in the game world
        //Returns null if hovering over a UI element or if input_capture is not set
        godot::Object* get_3d_canvas_mouse_position(int collision_mask, tog::TacticsControl* tactics_control);
        //Checks if the mouse is hovering over a UI element
        //Returns true if the mouse is over any of the specified UI elements
        bool is_mouse_hovering_ui_elem(tog::TacticsControl* tactics_control, std::initializer_list<std::string_view> elements = {"%Actions", "%Hints"}) {return false;};

    protected:
        static void _bind_methods() {}

    private:
        //Reference to the TacticsControlsResource
        godot::Ref<tog::TacticsControlResource> m_tactics_controls_resource;
        //tog::TacticsControlResource* m_tactics_controls_resource = nullptr;
        //Node for capturing mouse clicks
        godot::Node* m_input_capture = nullptr;

    };

}
