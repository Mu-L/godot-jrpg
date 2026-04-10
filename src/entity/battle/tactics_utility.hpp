#pragma once

#include "godot_cpp/classes/collision_shape3d.hpp"
#include "util/utility_vec.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/variant/vector3.hpp"

//remove the y value for a godot::Vector3 object
inline godot::Vector3 remove_y(const godot::Vector3 vec) {
    return vec * godot::Vector3(1, 0, 1);
}

//Calculates a Vector3 distance, removing the Y value from the result
inline float distance_without_y(godot::Vector3 a, godot::Vector3 b) {
    return remove_y(b).distance_to(remove_y(a));
}

//Converts child MeshInstance3D nodes into StaticBody3D nodes with TacticsTile script
//[param tiles_obj] The Node3D containing tile MeshInstance3D children to convert
//This function transforms 'Tiles' into the following structure:
//	> Tiles:                          > Tiles:
//		> Tile1                           > StaticBody3D (tile.gd):
//		> Tile2                               > Tile1
//		...                                   > CollisionShape3D
//		> TileN   -- TRANSFORM INTO ->    > StaticBody2 (tile.gd):
//											  > Tile2
//											  > CollisionShape3D
//												...
//Useful for configuring walkable tiles as efficiently as possible
inline void tiles_into_static_bodies(godot::Node3D* tiles) {

    for (auto& variant : tiles->get_children()) {
        godot::MeshInstance3D* mesh_node{godot::Object::cast_to<godot::MeshInstance3D>(variant)};
        if (!mesh_node) { continue; }

        //Create StaticBody3D child with collision
        mesh_node->create_trimesh_collision();

        godot::StaticBody3D* temp_body = godot::Object::cast_to<godot::StaticBody3D>(mesh_node->get_child(0));
        if (!temp_body) { continue; }

        godot::CollisionShape3D* temp_shape = godot::Object::cast_to<godot::CollisionShape3D>(temp_body->get_child(0));
        if (!temp_shape) { continue; }

        tog::TacticsTile* tile_static_body = memnew(tog::TacticsTile);
        tile_static_body->set_name(temp_body->get_name());
        tile_static_body->set_transform(temp_body->get_transform());

        //Move the generated collision shape onto the real tile
        temp_body->remove_child(temp_shape);
        tile_static_body->add_child(temp_shape);

        //Reparent the mesh under the real tile
        mesh_node->remove_child(temp_body);
        mesh_node->set_position(get_zero_vector3());
        tile_static_body->add_child(mesh_node);

        tiles->add_child(tile_static_body);
        tile_static_body->configure_tile();
        tile_static_body->set_process(true);

        temp_body->queue_free();
    }

}


