#pragma once

#include "tactics_participant.hpp"

namespace tog {

    class TacticsParticipant;

    class TacticsPlayer : public TacticsParticipant {
        GDCLASS(TacticsPlayer, TacticsParticipant);

    public:
        TacticsPlayer() = default;
        ~TacticsPlayer() override = default;

    protected:
        static void _bind_methods() {}

    private:

    };

}
