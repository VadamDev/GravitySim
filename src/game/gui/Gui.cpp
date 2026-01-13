#include "Gui.h"

#include <imgui.h>
#include "../../engine/clock/FixedStepClock.h"

namespace game
{
    void Gui::draw()
    {
        const engine::ProfilerEntry *updateProfiler = clock->getUpdateProfiler();
        const engine::ProfilerEntry *renderProfiler = clock->getRenderProfiler();

        ImGui::Begin("Testing ImGui");
        ImGui::Text(std::format("UPS: {} ({:.3f}ms) |", clock->getUPS(), updateProfiler->calculateSpentTimeAvgMs()).c_str()); ImGui::SameLine(); ImGui::Checkbox("Unlimited Fps", &bUnlimitedFps);
        ImGui::Text(std::format("FPS: {} ({:.3f}ms)", clock->getFPS(), renderProfiler->calculateSpentTimeAvgMs()).c_str());

        ImGui::NewLine();

        //Profilers
        if (ImGui::CollapsingHeader("Profilers"))
        {
            for (auto entry : clock->getProfiler().allEntries())
            {
                ImGui::Text(entry.getName().c_str());
                ImGui::Text(std::format("Avg: {:.3f}ms over {} calls", entry.calculateSpentTimeAvgMs(), entry.getNumCalls()).c_str());
                ImGui::Text(std::format("Spent {:.3f}ms last call", entry.getLastSpentTimeMs()).c_str());

                ImGui::NewLine();
            }
        }

        ImGui::End();

        //Process Choices

        //Unlimited FPS
        if (bUnlimitedFps != clock->bIgnoreFpsCap)
            clock->bIgnoreFpsCap = bUnlimitedFps;
    }
}
