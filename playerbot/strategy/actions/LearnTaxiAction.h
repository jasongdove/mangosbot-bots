#pragma once

#include "../Action.h"

namespace ai
{
    class LearnTaxiAction : public Action {
    public:
        LearnTaxiAction(PlayerbotAI* ai) : Action(ai, "learn taxi") {}
        virtual bool Execute(Event event);
    };
}