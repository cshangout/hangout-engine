#pragma once

#include <functional>
#include "input_key.h"

namespace HE {
    enum class InputDeviceType {
        Keyboard,
        Mouse,
        Gamepad
    };

    struct InputDeviceState {
        float value { 0.f };
    };

    using InputDeviceStateCallbackFunc = std::function<std::unordered_map<InputKey, InputDeviceState>(int)>;

    struct InputDevice {
        InputDeviceType Type;
        int Index;
        std::unordered_map<InputKey, InputDeviceState> CurrentState;
        InputDeviceStateCallbackFunc StateFunc;
    };
}