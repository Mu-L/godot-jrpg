#pragma once

#include <ranges>

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/button.hpp"

#include "util/scene.hpp"
#include "util/bind.hpp"
#include "core/constants.hpp"
#include "resources/class_stats.hpp"


namespace tog {

    class ClassSelection : public godot::Node {
        GDCLASS(ClassSelection, godot::Node);

    public:
        ClassSelection();
        ~ClassSelection() = default;

        void _ready() override;
        void _physics_process(double delta) override;

    protected:
        static void _bind_methods() {}

    private:
        godot::LocalVector<godot::Ref<ClassStats>> roles;

    };

}
