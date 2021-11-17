#pragma once
#include <cassert>
#include <string>

namespace HE {
    enum class InputKey {
        A,
        B,
        C,
        D,
        E,
        L_THUMB_X,
        L_THUMB_Y,
        R_THUMB_X,
        R_THUMB_Y,
        MOUSE_MOVE_X,
        MOUSE_MOVE_Y,
        MOUSE_RIGHT,
        MOUSE_LEFT,
        MOUSE_MIDDLE,
        UNKNOWN
    };

    enum class InputSource {
        Keyboard,
        Mouse,
        Gamepad,
        Unknown
    };

    struct InputAction {
        std::string ActionName {""};
        float Scale {1.f};
    };

    inline InputSource GetInputSourceFromKey(InputKey key) {
        switch(key) {
            case InputKey::A:
            case InputKey::B:
            case InputKey::C:
            case InputKey::D:
            case InputKey::E:
                return InputSource::Keyboard;
            case InputKey::L_THUMB_X:
            case InputKey::L_THUMB_Y:
            case InputKey::R_THUMB_X:
            case InputKey::R_THUMB_Y:
                return InputSource::Gamepad;
            case InputKey::MOUSE_MOVE_X:
            case InputKey::MOUSE_MOVE_Y:
            case InputKey::MOUSE_RIGHT:
            case InputKey::MOUSE_LEFT:
            case InputKey::MOUSE_MIDDLE:
                return InputSource::Mouse;
            default:
                assert(true && "Invalid Input Source!");
                return InputSource::Unknown;
        }
    }

}