#pragma once
#include "core/constants.hpp"
#include "util/bind.hpp"
#include "godot_cpp/classes/resource.hpp"

namespace tog {

    //Resource class for managing tactics controls and related signals
    class TacticsControlResource : public godot::Resource {
        GDCLASS(TacticsControlResource, godot::Resource);

    public:

        TacticsControlResource() = default;
        ~TacticsControlResource() override = default;

    protected:
        static void _bind_methods() {
           // rl::signal_binding<TacticsControlResource, tog::node::signal::TacticsControlResource::called_move_camera>::add<double>();
        }

    };

}

