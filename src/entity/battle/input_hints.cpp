#include "input_hints.hpp"

#include "core/constants.hpp"

#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/tween.hpp"

void tog::InputHints::_ready() {
    auto resource_loader = godot::ResourceLoader::get_singleton();
    m_tactics_controls_resource = resource_loader->load(tog::path::resource::battle::tactics_control_resource);

    m_controller_hints = godot::Object::cast_to<godot::Control>(get_node_or_null(tog::node::name::BattleTest::ControllerHints));

    m_tactics_controls_resource->m_input_hints_folded = true;
    //Force immediate update
    update_hints_visibility(true);

    //connect mouse signals
    m_controller_hints->connect(tog::node::signal::Control::mouse_entered, callable_mp(this, &InputHints::on_mouse_entered));
    m_controller_hints->connect(tog::node::signal::Control::mouse_exited, callable_mp(this, &InputHints::on_mouse_exited));
}

void tog::InputHints::_unhandled_input(const godot::Ref<godot::InputEvent>& p_event) {
    if (p_event->is_action_pressed("controller_hints")) {
        //Unfold hints when action is pressed
        on_mouse_entered();
    } else if (p_event->is_action_released("controller_hints")) {
        //Fold hints when action is released
        on_mouse_exited();
    }
}

void tog::InputHints::on_mouse_entered() {
    m_tactics_controls_resource->m_input_hints_folded = false;
    update_hints_visibility();
}

void tog::InputHints::on_mouse_exited() {
    m_tactics_controls_resource->m_input_hints_folded = true;
    update_hints_visibility();
}

void tog::InputHints::update_hints_visibility(bool force_immediate) {
    float target_x = m_tactics_controls_resource->m_input_hints_folded ? FOLDED_OFFSET : 0.0f;
    float target_alpha = m_tactics_controls_resource->m_input_hints_folded ? 0.3f : 1.0f;

    if (force_immediate) {
        auto new_pos = m_controller_hints->get_global_position();
        auto new_color = m_controller_hints->get_modulate();
        new_pos.x = target_x;
        new_color.a = target_alpha;
        m_controller_hints->set_global_position(new_pos);
        m_controller_hints->set_modulate(new_color);
    } else {
        auto tween = create_tween();
        tween->set_parallel(true);
        tween->set_trans(godot::Tween::TRANS_SINE);
        tween->set_ease(godot::Tween::EASE_IN_OUT);
        tween->tween_property(m_controller_hints, "position:x", target_x, ANIMATION_DURATION);
        tween->tween_property(m_controller_hints, "modulate:a", target_alpha, ANIMATION_DURATION);
    }

}
