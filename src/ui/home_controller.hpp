#pragma once

#include "resources/character/character_state.hpp"
#include "godot_cpp/classes/node.hpp"

namespace tog {

    //load the main_player resource and manages the players game home screen

    class HomeController : public godot::Node {
        GDCLASS(HomeController, godot::Node);
    public:

        HomeController();
        ~HomeController() override = default;

        void _ready() override;

    protected:
        static void _bind_methods() {}

    private:



    private:
        godot::Ref<tog::CharacterState> m_main_player_state{};
    };

}
