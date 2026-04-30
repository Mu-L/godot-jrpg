#include "tactics_debug.hpp"

#include "util/utility.hpp"


namespace tog::debug {

    struct DebugEntry {
        godot::Variant m_old_value{};
        std::string_view m_message{};
        bool m_has_old_value = false;
    };

    static std::flat_map<Topic, DebugEntry> debug_state = {
        {
            Topic::PAWN,
            DebugEntry{
                .m_message = "[ --- Pawn Update --- ] New pawn selected: "
            }
        },
        {
            Topic::PARTICIPANT_TURN,
            DebugEntry{
                .m_message = "[ --- Turn Update --- ] Switched participant: "
            }
        },
        {
            Topic::TURN_STAGE,
            DebugEntry{
                .m_message = "[ --- Turn Update --- ] Turn Stage: "
            }
        },
        {
            Topic::CAMERA_FOCUS,
            DebugEntry{
                .m_message = "[ --- Camera --- ] Camera focuses on: "
            }
        },
        {
            Topic::PLAYER_CAN_ACT,
            DebugEntry{
                .m_message = "[ --- Player Update --- ] Can player act?  "
            }
        },
        {
            Topic::NEAREST_TARGET_FOUND,
            DebugEntry{
                .m_message = "[ --- Turn Update ---  ] Destination found: "
            }
        },
        {
            Topic::NEAREST_TARGET,
            DebugEntry{
                .m_message = "[ --- Turn Update --- ] Not moving. No nearest target found for "
            }
        },
        {
            Topic::QUAD_SNAP,
            DebugEntry{
                .m_message = "[ --- Camera --- ] Quadrant Snapping (is_snapping_to_quad) : "
            }
        },
        {
            Topic::CAMERA_ROTATING,
            DebugEntry{
                .m_message = "[ --- Camera --- ] Camera Rotating (is_rotating) : "
            }
        },
        {
            Topic::IN_FREE_LOOK,
            DebugEntry{
                .m_message = "[ --- Camera --- ] Free Look (in_free_look) : "
            }
        }
    };

    static std::string inspect_variant(const godot::Variant& value) {
        switch (value.get_type()) {

            case godot::Variant::NIL: {
                return "null";
                break;
            }

            case godot::Variant::BOOL: {
                bool b = value;
                return b ? "true" : "false";
                break;
            }

            case godot::Variant::INT: {
                int64_t i = value;
                return fmt::to_string(i);
                break;
            }

            case godot::Variant::STRING: {
                godot::String str = value;
                return str.utf8().get_data();
                break;
            }

            case godot::Variant::OBJECT: {

                if ( godot::Object* obj{value}; obj != nullptr ) {
                    auto node = godot::Object::cast_to<godot::Node>(obj);
                    return to_std_string(node->get_name());
                }

                break;
            }

            default: {
                return "default";
                break;
            }

        }
        return "null";
    }

    static bool are_the_variants_equal(const godot::Variant& old_value, const godot::Variant& new_value) {
        if (old_value.get_type() != new_value.get_type()) { return false; }
        return old_value == new_value;
    }

    static void no_spam_log(const Topic topic, const godot::Variant& value) {
        //find if topic exist
        if (auto it = debug_state.find(topic); it != debug_state.end()) {

            //grab debug metadata
            DebugEntry& entry = it->second;

            //check if we have old value or if the values are equal
            if (entry.m_has_old_value && are_the_variants_equal(entry.m_old_value, value)) { return; }

            //grab logger
            static rl::Console<godot::RichTextLabel>*   logger{ rl::console::get() };

            //update metadata
            entry.m_old_value = value;
            entry.m_has_old_value = true;

            logger->print("{} {}", entry.m_message, inspect_variant(value));

        } else {
            return;
        }

    }

}
