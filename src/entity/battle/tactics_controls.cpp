#include "tactics_controls.hpp"

#include "godot_cpp/classes/resource_loader.hpp"

void tog::TacticsControls::_ready() {
    auto res_loader = godot::ResourceLoader::get_singleton();
    m_tactics_control_resource = res_loader->load(tog::path::resource::battle::tactics_control_resource);
    m_tactics_camera_resource = res_loader->load(tog::path::resource::battle::tactics_camera_resource);
    m_tactics_participant_resource = res_loader->load(tog::path::resource::battle::tactics_participant_resource);
    m_tactics_arena_resource = res_loader->load(tog::path::resource::battle::tactics_arena_resource);



    m_tactics_control_service = memnew(tog::TacticsControlsService(m_tactics_control_resource, m_tactics_camera_resource, m_tactics_participant_resource, m_tactics_arena_resource, m_input_capture));

}

void tog::TacticsControls::set_cursor_shape_to_move() {
}
