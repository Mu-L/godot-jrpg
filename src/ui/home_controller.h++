#pragma once
#include <godot_cpp/classes/node.hpp>
#include <utility>

namespace tog {

    /*
     *  Rotate buttons by 45 and reposition
     *  Route scene to appropriate functions
     *
     */

    class HomeController : public godot::Node {
        GDCLASS(HomeController, godot::Node);
    public:
        void _ready() override {

        };
    protected:
        static void _bind_methods() {}
    };

}
