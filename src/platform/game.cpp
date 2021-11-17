#include <hangout_engine/platform/game.h>
#include <hangout_engine/service_locator.h>
#include <rendering/opengl/open_gl_renderer.h>
#include "sdl_window.h"
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
            // If the X button was clicked, exit
            if (ServiceLocator::GetWindow()->Update()) {
                _instance->_running = false;
                return;
            }

            _instance->PhysicsUpdate(0.0f);
            _instance->Update(0.0f);

            _instance->Render();

        }
    }

    void Game::initializeServices() {
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
}