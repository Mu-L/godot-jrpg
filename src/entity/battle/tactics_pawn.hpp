#pragma once

#include "godot_cpp/classes/character_body3d.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace tog {

    //Represents a pawn in the tactics game, handling movement, combat, and state management
    class TacticsPawn : public godot::CharacterBody3D {
        GDCLASS(TacticsPawn, godot::CharacterBody3D);

    public:

        TacticsPawn() = default;
        ~TacticsPawn() override = default;

        void _ready() override {};

    protected:

        static void _bind_methods() {

        }

    private:

    };

}