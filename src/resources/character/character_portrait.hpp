#pragma once

#include "util/bind.hpp"
#include "core/attributes.hpp"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/core/class_db.hpp>


namespace tog {

    //This resource describes one sheet and how to split it into 6 portraits.
    class CharacterPortraitSheet : public godot::Resource {
        GDCLASS(CharacterPortraitSheet, godot::Resource);

    public:
        [[property]] void set_sheet(const godot::Ref<godot::Texture2D>& texture) { m_character_sprite_sheet = texture; }
        [[property]] godot::Ref<godot::Texture2D> get_sheet() const { return m_character_sprite_sheet; }

        [[property]] void set_ids(const godot::Array& arr) { m_ids = arr; }
        [[property]] godot::Array get_ids() const { return m_ids; }

        [[property]] void set_columns(const int value) { m_columns = value; }
        [[property]] int get_columns() const { return m_columns; }

        [[property]] void set_rows(const int value) { m_rows = value; }
        [[property]] int get_rows() const { return m_rows; }

        godot::Ref<godot::Texture2D> build_portrait_texture(int index) const;

        inline int get_count() const { return m_rows * m_columns; }

    protected:
        static void _bind_methods() {
            //bind properties to editor
            rl::bind_property(CharacterPortraitSheet, columns, int);
            rl::bind_property(CharacterPortraitSheet, rows, int);
            godot::ClassDB::bind_method(godot::D_METHOD("set_sheet", "sheet"), &CharacterPortraitSheet::set_sheet);
            godot::ClassDB::bind_method(godot::D_METHOD("get_sheet"), &CharacterPortraitSheet::get_sheet);
            ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "sheet", godot::PROPERTY_HINT_RESOURCE_TYPE,"Texture2D"), "set_sheet", "get_sheet");
            godot::ClassDB::bind_method(godot::D_METHOD("set_ids", "ids"), &CharacterPortraitSheet::set_ids);
            godot::ClassDB::bind_method(godot::D_METHOD("get_ids"), &CharacterPortraitSheet::get_ids);
            ADD_PROPERTY(godot::PropertyInfo(godot::Variant::ARRAY, "ids"), "set_ids", "get_ids");

        };


    private:
        godot::Ref<godot::Texture2D> m_character_sprite_sheet{};
        int m_columns = 3;
        int m_rows = 2;
        godot::Array m_ids;

    };
}
