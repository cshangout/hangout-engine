#pragma once
#include <hangout_engine/platform/window.h>

#include <SDL.h>
#include <cstdlib>
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#else
#endif

namespace HE {
    class SDLWindow : public Window {
    public:
        SDLWindow() = default;

        ~SDLWindow() override;

        bool Update() override;

        std::pair<int, int> GetWindowExtents() override;
        float GetAspectRatio() override;

        void OpenWindow(WindowData data) override;

        void MakeContextCurrent() override;
        void SwapBuffer() override;
        void SetManagedFunction(callback) override;
    private:
        SDL_Window* _window = nullptr;
        SDL_GLContext _context;

    };
}
