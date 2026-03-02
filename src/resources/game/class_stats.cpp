
#include "class_stats.hpp"

void tog::ClassStats::set_max_hp(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_max_hp = static_cast<int>(value * 1.2);
            break;
        case ClassName::SPEAR_BEARER:
            m_max_hp = static_cast<int>(value * 1.2);
            break;
        case ClassName::SCOUT:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::LIGHT_BEARER:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::JEONSULSA:
            m_max_hp = static_cast<int>(value * 1.1);
            break;
        case ClassName::HWAYEOMSA:
            m_max_hp = static_cast<int>(value * 1.1);
            break;
        case ClassName::DANSULSA:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::WONSULSA:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::ANIMA:
            m_max_hp = static_cast<int>(value * 1.0);
            break;
        case ClassName::DEFENDER:
            m_max_hp = static_cast<int>(value * 1.2);
            break;
        case ClassName::GUIDE:
            m_max_hp = static_cast<int>(value * .5);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_max_mp(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_max_mp = static_cast<int>(value * 1.0);
            break;
        case ClassName::SPEAR_BEARER:
            m_max_mp = static_cast<int>(value * 1.0);
            break;
        case ClassName::SCOUT:
            m_max_mp = static_cast<int>(value * 1.2);
            break;
        case ClassName::LIGHT_BEARER:
            m_max_mp = static_cast<int>(value * 1.3);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_max_mp = static_cast<int>(value * 1.3);
            break;
        case ClassName::JEONSULSA:
            m_max_mp = static_cast<int>(value * 1.3);
            break;
        case ClassName::HWAYEOMSA:
            m_max_mp = static_cast<int>(value * 1.4);
            break;
        case ClassName::DANSULSA:
            m_max_mp = static_cast<int>(value * 1.5);
            break;
        case ClassName::WONSULSA:
            m_max_mp = static_cast<int>(value * 1.5);
            break;
        case ClassName::ANIMA:
            m_max_mp = static_cast<int>(value * 1.2);
            break;
        case ClassName::DEFENDER:
            m_max_mp = static_cast<int>(value * 0.7);
            break;
        case ClassName::GUIDE:
            m_max_mp = static_cast<int>(value * .5);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_attack(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_attack = static_cast<int>(value * 1.2);
            break;
        case ClassName::SPEAR_BEARER:
            m_attack = static_cast<int>(value * 1.3);
            break;
        case ClassName::SCOUT:
            m_attack = static_cast<int>(value * 1.1);
            break;
        case ClassName::LIGHT_BEARER:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::JEONSULSA:
            m_attack = static_cast<int>(value * 1.3);
            break;
        case ClassName::HWAYEOMSA:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::DANSULSA:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::WONSULSA:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::ANIMA:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::DEFENDER:
            m_attack = static_cast<int>(value * 1.0);
            break;
        case ClassName::GUIDE:
            m_attack = static_cast<int>(value * .5);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_magic_power(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_magic_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::SPEAR_BEARER:
            m_magic_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::SCOUT:
            m_magic_power = static_cast<int>(value * 1.2);
            break;
        case ClassName::LIGHT_BEARER:
            m_magic_power = static_cast<int>(value * 1.3);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_magic_power = static_cast<int>(value * 1.3);
            break;
        case ClassName::JEONSULSA:
            m_magic_power = static_cast<int>(value * 1.3);
            break;
        case ClassName::HWAYEOMSA:
            m_magic_power = static_cast<int>(value * 1.4);
            break;
        case ClassName::DANSULSA:
            m_magic_power = static_cast<int>(value * 1.5);
            break;
        case ClassName::WONSULSA:
            m_magic_power = static_cast<int>(value * 1.5);
            break;
        case ClassName::ANIMA:
            m_magic_power = static_cast<int>(value * 1.2);
            break;
        case ClassName::DEFENDER:
            m_magic_power = static_cast<int>(value * 0.7);
            break;
        case ClassName::GUIDE:
            m_magic_power = static_cast<int>(value * .5);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_defense(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_defence = static_cast<int>(value * 1.2);
            break;
        case ClassName::SPEAR_BEARER:
            m_defence = static_cast<int>(value * 1.2);
            break;
        case ClassName::SCOUT:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::LIGHT_BEARER:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::JEONSULSA:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::HWAYEOMSA:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::DANSULSA:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::WONSULSA:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::ANIMA:
            m_defence = static_cast<int>(value * 1.0);
            break;
        case ClassName::DEFENDER:
            m_defence = static_cast<int>(value * 1.5);
            break;
        case ClassName::GUIDE:
            m_defence = static_cast<int>(value * .5);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_spirit_power(const int value) {

    switch (m_class_name) {
        case ClassName::FISHERMAN:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::SPEAR_BEARER:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::SCOUT:
            m_spirit_power = static_cast<int>(value * 1.2);
            break;
        case ClassName::LIGHT_BEARER:
            m_spirit_power = static_cast<int>(value * 1.3);
            break;
        case ClassName::WAVE_CONTROLLER:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::JEONSULSA:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::HWAYEOMSA:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::DANSULSA:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::WONSULSA:
            m_spirit_power = static_cast<int>(value * 1.0);
            break;
        case ClassName::ANIMA:
            m_spirit_power = static_cast<int>(value * 1.3);
            break;
        case ClassName::DEFENDER:
            m_spirit_power = static_cast<int>(value * .7);
            break;
        case ClassName::GUIDE:
            m_spirit_power = static_cast<int>(value * 2.0);
            break;
        case ClassName::MAX_CLASS_COUNT:
        default:
            break;
    }

}

void tog::ClassStats::set_class_name(const int value) {
    m_class_name = static_cast<ClassName>(value);
    set_max_hp(10);
    set_max_mp(10);
    set_attack(10);
    set_magic_power(10);
    set_defense(10);
    set_spirit_power(10);
}
