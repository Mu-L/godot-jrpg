#include "character_state.hpp"

void tog::CharacterState::_bind_methods() {
    rl::bind_property(CharacterState, name, godot::String);
    rl::bind_property(CharacterState, level, int);
    rl::bind_property(CharacterState, xp, int);
    rl::bind_property(CharacterState, hp, int);
    rl::bind_property(CharacterState, shinsu, int);
    rl::bind_property(CharacterState, defense, int);
    rl::bind_property(CharacterState, attack, int);
    rl::bind_property(CharacterState, magic_power, int);
    rl::bind_property(CharacterState, spirit_power, int);
}
