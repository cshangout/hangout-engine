#pragma once
#include <string>
#include <functional>

namespace HE {
    struct WindowData {
        std::string title;
        uint32_t width, height;
    };

    typedef void(*callback)();

    class Window {
    public:
        virtual ~Window() = default;
        virtual void OpenWindow(WindowData data) = 0;
        virtual bool Update() = 0;
        virtual void MakeContextCurrent() = 0;

        virtual std::pair<int, int> GetWindowExtents() = 0;
        virtual float GetAspectRatio() = 0;
        virtual void SwapBuffer() = 0;
        virtual bool IsManagedGameLoop() { return _managed; }
        virtual void SetManagedFunction(callback) = 0;
    protected:
        bool _managed { false };
    };
}