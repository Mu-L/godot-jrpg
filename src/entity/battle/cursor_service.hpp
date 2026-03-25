#pragma once

#include "godot_cpp/classes/object.hpp"

namespace tog {

    //Handles cursor-related functions for the Tactics system
    class CursorService : public godot::Object {
        GDCLASS(CursorService, godot::Object);

    public:
        CursorService() = default;
        ~CursorService() override = default;

        static void set_cursor_shape_to_move();
        static void set_cursor_shape_to_arrow();


    protected:
        void static _bind_methods() {}

    private:

    };

}

