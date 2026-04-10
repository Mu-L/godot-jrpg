#include "tactics_tile.hpp"

#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "util/conversions.hpp"
#include "util/scene.hpp"

tog::TacticsTile::TacticsTile() {
    m_hover_material = make_colored_material(godot::Color::html("#FFFFFF3F"));
    m_reachable_material = make_colored_material(godot::Color::html("#008fdbBF"));
    m_hover_reachable_material = make_colored_material(godot::Color::html("#0aa9ffBF"));
    m_attackable_material = make_colored_material(godot::Color::html("#d10000BF"));
    m_hover_attackable_material = make_colored_material(godot::Color::html("#ff4242BF"));
}

void tog::TacticsTile::_process(double p_delta) {
    //Get child node named "Tile" and cast it to a MeshInstance3D.
    godot::MeshInstance3D* tile_node = rl::gdcast<godot::MeshInstance3D>(get_node_or_null(tog::node::name::BattleTest::Tile));

    if (!tile_node)
        return;

    //Set visibility of the tile to visible if attackable, reachable, or hover are true
    tile_node->set_visible(m_attackable || m_reachable || m_hover);

    if (m_hover) {
        //If hover is true, decide which material to use based on the tile's state
        if (m_reachable) {
            tile_node->set_material_override(m_hover_reachable_material);
        } else if (m_attackable) {
            tile_node->set_material_override(m_hover_attackable_material);
        } else {
            tile_node->set_material_override(m_hover_material);
        }
    } else {
        //If hover is false, this block decides between two materials
        if (m_reachable) {
            tile_node->set_material_override(m_reachable_material);
        } else if (m_attackable) {
            tile_node->set_material_override(m_attackable_material);
        }
    }

}

godot::TypedArray<godot::Node3D> tog::TacticsTile::get_neighbors(float height) {
    tog::TacticsTileRaycast* raycast_node = rl::gdcast<tog::TacticsTileRaycast>(get_node_or_null("RayCasting"));
    return raycast_node->get_all_neighbors(height);
}

godot::Object* tog::TacticsTile::get_tile_occupier() {
    tog::TacticsTileRaycast* raycast_node = rl::gdcast<tog::TacticsTileRaycast>(get_node_or_null("RayCasting"));
    return raycast_node->get_object_above();
}

bool tog::TacticsTile::is_taken() {
    return get_tile_occupier() != nullptr;
}

void tog::TacticsTile::reset_markers() {
    m_path_finding_distance = 0;
    m_path_finding_root_tile = nullptr;
    m_reachable = false;
    m_attackable = false;
}

void tog::TacticsTile::configure_tile() {
    m_hover = false;
    const auto node = m_tactics_tile_raycast_scene.instantiate();
    attach_child_to_parent(this, node);
    reset_markers();
}