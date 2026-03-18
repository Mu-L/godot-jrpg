#include "tactics_tile_raycast.hpp"

#include "util/conversions.hpp"
#include "godot_cpp/classes/ray_cast3d.hpp"

godot::Array tog::TacticsTileRaycast::get_all_neighbors(float height) {
    godot::TypedArray<Node3D> neighbors;

    const Node3D* neighbors_node = this->get_node<godot::Node3D>(tog::node::name::RayCasting::Neighbors);
    assertion(neighbors_node, "MainMenu scene does not exist");

    auto children = neighbors_node->get_children();

    //godot::Array children = neighbors-

    for (auto node : children) {

        auto* child = rl::gdcast<godot::RayCast3D>(node.get_validated_object());

    }

    return {};
}
