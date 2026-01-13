#pragma once

#include "../../engine/window/imgui/ImGuiWindow.h"
#include "../../engine/AbstractGame.h"
#include "../../engine/clock/FixedStepClock.h"

namespace game
{
    class Gui : public engine::ImGuiWindow
    {

    public:
        explicit Gui(const engine::AbstractGame *game)
            : window(game->getWindow()), clock(dynamic_cast<engine::FixedStepClock*>(game->getClock())) {}

        void draw() override;

        bool shouldDraw() override
        {
            return true;
        }

    private:
        engine::Window &window;
        engine::FixedStepClock *clock;

        bool bUnlimitedFps = false;
    };
}
