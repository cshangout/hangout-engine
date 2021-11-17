#pragma once
#include <memory>
#include <hangout_engine/platform/window.h>
#include <hangout_engine/rendering/renderer.h>

namespace HE {
    class ServiceLocator {
    public:
        static inline const std::unique_ptr<Window> &GetWindow() { return _window; }
        static inline const std::unique_ptr<Renderer> &GetRenderer() { return _renderer; }

        static inline void Provide(Window *window) {
            if (_window) {
                shutdownWindow();
            }

            _window = std::unique_ptr<Window>(window);
        }

        static inline void Provide(Renderer *renderer) {
            if (_renderer) {
                shutdownRenderer();
            }
            _renderer = std::unique_ptr<Renderer>(renderer);
        }

        static inline void ShutdownServices() {
            // ensure we shut down services in the correct order
            // usually opposite order of initialized.
            shutdownRenderer();
            shutdownWindow();
        }

    private:

        static inline std::unique_ptr<Window> _window = nullptr;
        static inline std::unique_ptr<Renderer> _renderer = nullptr;

        static inline void shutdownRenderer() {
            _renderer.reset();
            _renderer = nullptr;
        }
        
        static inline void shutdownWindow() {
            _window.reset();
            _window = nullptr;
        }

    };
}