#include "home_controller.hpp"

#include "core/constants.hpp"

#include "godot_cpp/classes/resource_loader.hpp"


tog::HomeController::HomeController() {
    m_main_player_state =  godot::ResourceLoader::get_singleton()->load(tog::path::resource::player::main_player);

}

void tog::HomeController::_ready() {
    //display_character_info
}
