#pragma once
#include <unordered_map>
#include <hangout_engine/input/input_key.h>
#include <hangout_engine/input/input_devices.h>
#include <SDL_types.h>

namespace HE {
    class SDLInput {
    public:
        std::unordered_map<InputKey, InputDeviceState> GetKeyboardState(int) { return _keyboardState; }
        std::unordered_map<InputKey, InputDeviceState> GetMouseState(int) { return _mouseState; }
        std::unordered_map<InputKey, InputDeviceState> GetGamepadState(int index) { return _gamepadStates[index]; }

        void UpdateKeyboardState(const Uint8* keyboardState);
        void UpdateMouseState(Uint32 buttons, int x, int y);

    private:
        InputKey sdlKeyToInputKey(Uint8 key);

    private:
        std::unordered_map<InputKey, InputDeviceState> _keyboardState {};
        std::unordered_map<InputKey, InputDeviceState> _mouseState {};
        std::unordered_map<int, std::unordered_map<InputKey, InputDeviceState>> _gamepadStates {};
    };
}


