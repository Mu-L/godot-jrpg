#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/core/class_db.hpp>

class character_portrait
{
};

namespace tog {
    class CharacterPortraitSheet : public godot::Resource {
        GDCLASS(CharacterPortraitSheet, godot::Resource);

    };
}