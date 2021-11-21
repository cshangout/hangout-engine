//
// Created by Paul Mauviel on 2021-11-08.
//

#include "sdl_window.h"

#include <iostream>
#include <hangout_engine/service_locator.h>
#include <rendering/opengl/open_gl_graphics.h>

namespace HE {
    bool SDLWindow::Update() {
        auto* inputManager = ServiceLocator::GetInputManager();

        SDL_Event event;
        while ((SDL_PollEvent(&event)) != 0) {
            // Do stuff with events
            if (event.type == SDL_QUIT) return true;

            if (event.type == SDL_CONTROLLERDEVICEADDED) {
                std::cout << "Controller connected" << std::endl;
                if (inputManager) {
                    SDL_GameController* pad = SDL_GameControllerOpen(event.cdevice.which);
                    _input.AddController(pad);

                    auto id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad));
                    inputManager->RegisterDevice(InputDevice {
                            .Type = InputSource::Gamepad,
                            .Index = static_cast<int>(id),
                            .StateFunc = std::bind(&SDLInput::GetGamepadState, &_input, std::placeholders::_1)
                    });
                }
            }

            if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
                std::cout << "Controller disconnected" << std::endl;
                auto id = event.cdevice.which;
                _input.RemoveController(id);

                if (inputManager) {
                    inputManager->RemoveDevice(InputSource::Gamepad, static_cast<int>(id));
                }
            }
        }

        auto keyState = SDL_GetKeyboardState(nullptr);
        _input.UpdateKeyboardState(keyState);

        int mouseX, mouseY;

        auto buttons = SDL_GetMouseState(&mouseX, &mouseY);
        _input.UpdateMouseState(buttons, mouseX, mouseY);

        return false;
    }

    std::pair<int, int> SDLWindow::GetWindowExtents() {
        int width, height;

        SDL_GL_GetDrawableSize(_window, &width, &height);

        return { width, height };
    }

    float SDLWindow::GetAspectRatio() {
        auto [width, height] = GetWindowExtents();
        return static_cast<float>(width) / static_cast<float>(height);
    }

    void SDLWindow::OpenWindow(WindowData data) {
#if __EMSCRIPTEN__
      _managed = true;
#endif

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
            throw std::runtime_error("Failed to initialize SDL!");
        }

        auto width = data.width;
        auto height = data.height;

        // TODO: The renderer part (OpenGL) should be separated from the window creation.
        // This should be good enough for gamejam however.
        _window = SDL_CreateWindow(data.title.c_str(),
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   static_cast<int>(width), static_cast<int>(height),
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);



#if !__EMSCRIPTEN__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

        _context = SDL_GL_CreateContext(_window);
        SDL_GL_SetSwapInterval(0);
        MakeContextCurrent();

        auto* inputManager = ServiceLocator::GetInputManager();

        inputManager->RegisterDevice(InputDevice {
            .Type = InputSource::Keyboard,
            .Index = 0,
            .StateFunc = std::bind(&SDLInput::GetKeyboardState, &_input, std::placeholders::_1)
        });

        inputManager->RegisterDevice(InputDevice {
            .Type = InputSource::Mouse,
            .Index = 0,
            .StateFunc = std::bind(&SDLInput::GetMouseState, &_input, std::placeholders::_1)
        });
    }

    SDLWindow::~SDLWindow() {
        SDL_Quit();
    }

    void SDLWindow::MakeContextCurrent() {
        SDL_GL_MakeCurrent(_window, _context);
    }

    void SDLWindow::SwapBuffer() {
        SDL_GL_SwapWindow(_window);
    }

    void SDLWindow::SetManagedFunction(callback function) {
#if __EMSCRIPTEN__
        emscripten_set_main_loop(function, 0, 1);
#endif
    }


}