#pragma once

#include "singletons/console.hpp"

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/char_string.hpp>

#include <flat_map>

namespace tog::debug {

    enum class Topic {
        PAWN,
        PARTICIPANT_TURN,
        TURN_STAGE,
        CAMERA_FOCUS,
        PLAYER_CAN_ACT,
        NEAREST_TARGET_FOUND,
        NEAREST_TARGET,
        QUAD_SNAP,
        CAMERA_ROTATING,
        IN_FREE_LOOK,
        MAX_TOPIC_COUNT
    };

    struct DebugEntry {
        godot::Variant m_old_value{};
        std::string_view m_message{};
        bool m_has_old_value = false;
    };

    class Logger : public godot::Object {
        GDCLASS(Logger, godot::Object);
    public:
        Logger();

        ~Logger() override {
            m_static_inst = nullptr;
        }

        static inline tog::debug::Logger* get() {
            return m_static_inst;
        }

        void no_spam_log(const Topic topic, const godot::Variant &value);

    private:
        bool are_the_variants_equal(const godot::Variant& old_value, const godot::Variant& new_value);
        std::string inspect_variant(const godot::Variant& value);

    protected:
        static void _bind_methods() {}
    private:
        rl::Console<godot::RichTextLabel>*  m_console{ rl::console::get() };
        static inline Logger* m_static_inst{ nullptr };
        std::flat_map<Topic, DebugEntry> debug_state;
    };

}

