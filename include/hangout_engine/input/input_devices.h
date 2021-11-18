#pragma once

#include <functional>
#include "input_key.h"

namespace HE {
    struct InputDeviceState {
        float value { 0.f };
    };

    using InputDeviceStateCallbackFunc = std::function<std::unordered_map<InputKey, InputDeviceState>(int)>;

    struct InputDevice {
        InputSource Type { InputSource::Unknown };
        int Index { -1 };
        std::unordered_map<InputKey, InputDeviceState> CurrentState {};
        InputDeviceStateCallbackFunc StateFunc = nullptr;
    };
}