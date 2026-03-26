#pragma once

#include "tactics_control.hpp"
#include "resources/battle/tactics_control_resource.hpp"
#include "godot_cpp/classes/object.hpp"

namespace tog {

    //Service class for managing input-related functionalities in the Tactics game
    class TacticsControlsInputService : public godot::Object {
        GDCLASS(TacticsControlsInputService, godot::Object);

    public:
        TacticsControlsInputService() = default;
        TacticsControlsInputService(tog::TacticsControlResource* controls, godot::Node* input_capture);
        ~TacticsControlsInputService() override = default;

        void update_mouse_mode();
        void handle_input();
        godot::Object* get_3d_canvas_mouse_position(int collision_mask, tog::TacticsControl tactics_control);
        void is_mouse_hovering_ui_elem(tog::TacticsControl* tactics_control, )


    protected:
        static void _bind_methods() {}

    private:
        //Reference to the TacticsControlsResource
        tog::TacticsControlResource* m_tactics_controls_resource = nullptr;
        //Node for capturing mouse clicks
        godot::Node* m_input_capture = nullptr;

    };

}
