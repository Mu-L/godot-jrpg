#include "tactics_tile_raycast.hpp"

#include "godot_cpp/core/math.hpp"
#include "godot_cpp/classes/ray_cast3d.hpp"
#include "util/conversions.hpp"

godot::TypedArray<godot::Node3D>  tog::TacticsTileRaycast::get_all_neighbors(float height) {
    //an array of neighboring Node3D objects (typically TacticsTiles)
    godot::TypedArray<Node3D> neighbors;
    //array of child nodes (RayCast3D nodes)
    godot::Array children =  get_node<godot::Node3D>(tog::node::name::RayCasting::Neighbors)->get_children();
    //grab the parent node
    auto* parent = Object::cast_to<Node3D>(get_parent());

    //iterate through all the child nodes
    for (const auto& node : children) {
        //Convert the obj type from Variant to the actual Node Type
        auto* ray = godot::Object::cast_to<godot::RayCast3D>(node.get_validated_object());
        //Get the object hit by the ray
        auto* collided_node = godot::Object::cast_to<godot::Node3D>(ray->get_collider());
        //check if object exists and is within the specified height range
        if (collided_node && ( godot::Math::abs(collided_node->get_global_position().y - parent->get_global_position().y) <= height) ) {
            neighbors.append(collided_node);
        }
    }

    return neighbors;
}

godot::Object* tog::TacticsTileRaycast::get_object_above() {
    //Return object hit by the upward-facing ray
    return get_node<godot::RayCast3D>(tog::node::name::RayCasting::Above)->get_collider();
}
