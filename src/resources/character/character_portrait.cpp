#include "character_portrait.hpp"

#include "godot_cpp/classes/atlas_texture.hpp"

godot::Ref<godot::Texture2D> tog::CharacterPortraitSheet::build_portrait_texture(int index) const {
    //check if index is valid
    if ( !m_character_sprite_sheet.is_valid() || m_columns <= 0 || m_rows <= 0 || index < 0 || index >= get_count() ) {
        return {};
    }

    // calculate cell size from actual texture dimensions
    const int texture_width = m_character_sprite_sheet->get_width();
    const int texture_height = m_character_sprite_sheet->get_height();
    const int cell_width = texture_width/m_columns;
    const int cell_height = texture_height/m_rows;

    //calculate the uv coords of the portrait with respect to index value
    const int col_index = index % m_columns;
    const int row_index = index / m_columns;
    const float x = float(col_index * cell_width);
    const float y = float(row_index * cell_height);
    const float w = float(cell_width);
    const float h = float(cell_height);

    //create "sub-texture"
    godot::Ref<godot::AtlasTexture> portrait_texture;
    portrait_texture.instantiate();
    portrait_texture->set_atlas(m_character_sprite_sheet);
    portrait_texture->set_region(godot::Rect2(godot::Vector2(x, y), godot::Vector2(w, h)));

    return portrait_texture;
}
