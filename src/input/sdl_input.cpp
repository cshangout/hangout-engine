#include <SDL_scancode.h>
#include <SDL_mouse.h>
#include "sdl_input.h"

namespace HE {

    void SDLInput::UpdateKeyboardState(const Uint8* keyboardState) {
        for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
            InputKey key = sdlKeyToInputKey(i);
            // skip unsupported keys
            if (key == InputKey::UNKNOWN) continue;

            auto value = static_cast<float>(keyboardState[static_cast<Uint8>(i)]);
            _keyboardState[key].value = value;
        }
    }

    InputKey SDLInput::sdlKeyToInputKey(Uint8 key) {
        switch(key) {
            case SDL_SCANCODE_A:
                return InputKey::A;
            case SDL_SCANCODE_B:
                return InputKey::B;
            case SDL_SCANCODE_C:
                return InputKey::C;
            case SDL_SCANCODE_D:
                return InputKey::D;
            case SDL_SCANCODE_E:
                return InputKey::E;
            default:
                return InputKey::UNKNOWN;
        }
    }

    void SDLInput::UpdateMouseState(Uint32 buttons, int x, int y) {
        _mouseState[InputKey::MOUSE_LEFT].value = static_cast<float>((buttons & SDL_BUTTON_LMASK) != 0);
        _mouseState[InputKey::MOUSE_RIGHT].value = static_cast<float>((buttons & SDL_BUTTON_RMASK) != 0);
        _mouseState[InputKey::MOUSE_MIDDLE].value = static_cast<float>((buttons & SDL_BUTTON_MMASK) != 0);
    }
}