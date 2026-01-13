#pragma once

namespace engine
{
    class ImGuiWindow
    {

    public:
        virtual ~ImGuiWindow() = default;

        virtual void draw() = 0;
        virtual bool shouldDraw() = 0;
    };
}
