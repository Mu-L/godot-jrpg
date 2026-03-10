#pragma once

#include "godot_cpp/classes/node.hpp"

#include <concepts>


template <typename Parent, typename Child>
requires std::derived_from<Parent, godot::Node> && std::derived_from<Child, godot::Node>
Child* attach_owned_child_node(Parent* parent, Child* child, bool editable = true) {
    if (!parent || !child)
        return nullptr;



}