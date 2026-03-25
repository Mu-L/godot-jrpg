#include "cursor_service.hpp"

#include "godot_cpp/classes/input.hpp"

void tog::CursorService::set_cursor_shape_to_move() {
    godot::Input *input = godot::Input::get_singleton();
    if (input->get_current_cursor_shape() != godot::Input::CURSOR_MOVE) {
        input->set_default_cursor_shape(godot::Input::CURSOR_MOVE);
    }
}

void tog::CursorService::set_cursor_shape_to_arrow() {
    godot::Input *input = godot::Input::get_singleton();
    if (input->get_current_cursor_shape() != godot::Input::CURSOR_ARROW) {
        input->set_default_cursor_shape(godot::Input::CURSOR_ARROW);
    }
}
