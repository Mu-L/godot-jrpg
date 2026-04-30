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

    static void no_spam_log(const Topic topic, const godot::Variant &value);

}

