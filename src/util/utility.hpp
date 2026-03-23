#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/standard_material3d.hpp"

#include <concepts>


namespace tog {

    template <typename Parent, typename Child>
    requires std::derived_from<Parent, godot::Node> && std::derived_from<Child, godot::Node>
    Child* attach_child_to_parent(Parent* parent, Child* child, bool editable = true) {
        if (!parent || !child)
            return nullptr;

        //remove old parent of child
        if (child->get_parent())
            child->get_parent()->remove_child(child);

        //attach scene to current node as sub child
        parent->add_child(child);
        //set the owner of the newly loaded scene to the current node
        child->set_owner(parent);
        //makes the newly loaded scene show up in the editor for debugging
        parent->set_editable_instance(child, editable);
        return child;
    }

    static godot::Ref<godot::StandardMaterial3D> make_colored_material(const godot::Color &color) {
        godot::Ref<godot::StandardMaterial3D> mat;
        mat.instantiate();
        mat->set_albedo(color);
        mat->set_roughness(0.9);
        mat->set_metallic(0.0);
        return mat;
    }

}
