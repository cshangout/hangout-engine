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
                return InputKey::KEY_A;
            case SDL_SCANCODE_B:
                return InputKey::KEY_B;
            case SDL_SCANCODE_C:
                return InputKey::KEY_C;
            case SDL_SCANCODE_D:
                return InputKey::KEY_D;
            case SDL_SCANCODE_E:
                return InputKey::KEY_E;
            default:
                return InputKey::UNKNOWN;
        }
    }

    void SDLInput::UpdateMouseState(Uint32 buttons, int x, int y) {
        _mouseState[InputKey::MOUSE_LEFT].value = static_cast<float>((buttons & SDL_BUTTON_LMASK) != 0);
        _mouseState[InputKey::MOUSE_RIGHT].value = static_cast<float>((buttons & SDL_BUTTON_RMASK) != 0);
        _mouseState[InputKey::MOUSE_MIDDLE].value = static_cast<float>((buttons & SDL_BUTTON_MMASK) != 0);
    }

    void SDLInput::AddController(SDL_GameController *newJoystick) {
        auto id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(newJoystick));
        _connectedControllers[id] = newJoystick;
    }

    void SDLInput::RemoveController(SDL_JoystickID id) {
        _connectedControllers.erase(id);
    }

    std::unordered_map<InputKey, InputDeviceState> SDLInput::GetGamepadState(int index) {
        std::unordered_map<InputKey, InputDeviceState> state {};

        auto joystickId = static_cast<SDL_JoystickID>(index);

        if (_connectedControllers.find(joystickId) == _connectedControllers.end()) return {};

        auto* controller = _connectedControllers[joystickId];

        // Get Buttons
        for (Uint8 i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
            auto pressed = SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(i));

            auto inputKey = sdlControllerButtonToInputKey(static_cast<SDL_GameControllerButton>(i));

            state[inputKey] = InputDeviceState {
                .value = static_cast<float>(pressed)
            };
        }

        // Get Axes
        for (Uint8 i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++) {
            auto pressed = SDL_GameControllerGetAxis(controller, static_cast<SDL_GameControllerAxis>(i));

            float value = 0.f;

            if (pressed > 0) {
                value = static_cast<float>(pressed) / 32767.0f;
            } else {
                value = static_cast<float>(pressed) / 32768.0f;
            }
            auto inputKey = sdlControllerAxisToInputKey(static_cast<SDL_GameControllerAxis>(i));

            state[inputKey] = InputDeviceState {
                    .value = value
            };
        }

        return state;
    }

    InputKey SDLInput::sdlControllerButtonToInputKey(SDL_GameControllerButton button) {
        switch (button) {
            case SDL_CONTROLLER_BUTTON_A:
                return InputKey::CONTROLLER_BUTTON_A;
            case SDL_CONTROLLER_BUTTON_B:
                return InputKey::CONTROLLER_BUTTON_B;
            case SDL_CONTROLLER_BUTTON_X:
                return InputKey::CONTROLLER_BUTTON_X;
            case SDL_CONTROLLER_BUTTON_Y:
                return InputKey::CONTROLLER_BUTTON_Y;
            case SDL_CONTROLLER_BUTTON_BACK:
                return InputKey::CONTROLLER_BUTTON_SELECT;
            case SDL_CONTROLLER_BUTTON_GUIDE:
                return InputKey::CONTROLLER_BUTTON_GUIDE;
            case SDL_CONTROLLER_BUTTON_START:
                return InputKey::CONTROLLER_BUTTON_START;
            case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                return InputKey::CONTROLLER_BUTTON_LEFTSTICK;
            case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                return InputKey::CONTROLLER_BUTTON_RIGHTSTICK;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                return InputKey::CONTROLLER_BUTTON_LEFTSHOULDER;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                return InputKey::CONTROLLER_BUTTON_RIGHTSHOULDER;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                return InputKey::CONTROLLER_BUTTON_DPAD_UP;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                return InputKey::CONTROLLER_BUTTON_DPAD_DOWN;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                return InputKey::CONTROLLER_BUTTON_DPAD_LEFT;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                return InputKey::CONTROLLER_BUTTON_DPAD_RIGHT;
            case SDL_CONTROLLER_BUTTON_MISC1:
                return InputKey::CONTROLLER_BUTTON_MISC1;
            case SDL_CONTROLLER_BUTTON_PADDLE1:
                return InputKey::CONTROLLER_BUTTON_PADDLE1;
            case SDL_CONTROLLER_BUTTON_PADDLE2:
                return InputKey::CONTROLLER_BUTTON_PADDLE2;
            case SDL_CONTROLLER_BUTTON_PADDLE3:
                return InputKey::CONTROLLER_BUTTON_PADDLE3;
            case SDL_CONTROLLER_BUTTON_PADDLE4:
                return InputKey::CONTROLLER_BUTTON_PADDLE4;
            case SDL_CONTROLLER_BUTTON_TOUCHPAD:
                return InputKey::CONTROLLER_BUTTON_TOUCHPAD;
            default:
                return InputKey::UNKNOWN;
        }
    }

    InputKey SDLInput::sdlControllerAxisToInputKey(SDL_GameControllerAxis axis) {
        switch (axis) {
            case SDL_CONTROLLER_AXIS_LEFTX:
                return InputKey::CONTROLLER_AXIS_LEFTX;
            case SDL_CONTROLLER_AXIS_LEFTY:
                return InputKey::CONTROLLER_AXIS_LEFTY;
            case SDL_CONTROLLER_AXIS_RIGHTX:
                return InputKey::CONTROLLER_AXIS_RIGHTX;
            case SDL_CONTROLLER_AXIS_RIGHTY:
                return InputKey::CONTROLLER_AXIS_RIGHTY;
            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                return InputKey::CONTROLLER_AXIS_TRIGGERLEFT;
            case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                return InputKey::CONTROLLER_AXIS_TRIGGERRIGHT;
            default:
                return InputKey::UNKNOWN;
        }
    }
}