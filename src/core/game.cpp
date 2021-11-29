#include <hangout_engine/core/game.h>
#include <hangout_engine/service_locator.h>
#include <rendering/opengl/open_gl_renderer.h>
#include <chrono>

#include <platform/sdl_window.h>

namespace HE {
    Game* Game::_instance = nullptr;

    Game::Game() : Game("New CS Hangouts Game Engine") {
    }

    Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(false) {
        initializeServices();
        _instance = this;
    }

    Game::~Game() {
        shutdownServices();
    }

    void Game::Run() {
        _running = true;
        Init();
        // Hook into managed loop here
        if (ServiceLocator::GetWindow()->IsManagedGameLoop()) {
            ServiceLocator::GetWindow()->SetManagedFunction(Game::gameLoop);
        } else {
            while (_instance->_running) {
                gameLoop();
            }
        }
    }

    void Game::gameLoop() {
        if (_instance != nullptr) {
            auto start = SDL_GetPerformanceCounter();

            auto deltaTime = static_cast<double>(start - _instance->_lastFrame) /
                    static_cast<double>(SDL_GetPerformanceFrequency());

            // If the X button was clicked, exit
            if (ServiceLocator::GetWindow()->Update()) {
                _instance->_running = false;
                return;
            }

            if (ServiceLocator::GetInputManager()) {
                ServiceLocator::GetInputManager()->processInput();
            }

            _instance->PhysicsUpdate(deltaTime);
            _instance->Update(deltaTime);

            _instance->render();

            _instance->_lastFrame = SDL_GetPerformanceCounter();

            double elapsed = static_cast<double>(_instance->_lastFrame - start) /
                    static_cast<double>(SDL_GetPerformanceFrequency()) * 1000.0f;

            auto delayTime = std::clamp((1000.0 / _instance->_desiredFPS) - elapsed, 0.0, 1000.0);
            SDL_Delay(std::floor(delayTime));
        }
    }

    void Game::initializeServices() {
        // Provide input manager
        ServiceLocator::Provide(new InputManager());

        ServiceLocator::Provide(new SDLWindow());
        ServiceLocator::GetWindow()->OpenWindow({
            .title = _title,
            .width = 800,
            .height = 600
        });

        ServiceLocator::Provide(new OpenGLRenderer());
        ServiceLocator::GetRenderer()->Init({});
    }

    void Game::shutdownServices() {}

    void Game::render() {
        _scene.Render();
    }
}