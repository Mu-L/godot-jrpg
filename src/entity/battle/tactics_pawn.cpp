#include "tactics_pawn.hpp"

#include "godot_cpp/classes/ray_cast3d.hpp"

tog::TacticsTile* tog::TacticsPawn::get_tile() const {
    return rl::gdcast<TacticsTile>(get_node<godot::RayCast3D>(tog::node::name::BattleTest::Tile)->get_collider());
}
