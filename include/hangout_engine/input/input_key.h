#pragma once
#include <cassert>
#include <string>

namespace HE {
    enum class InputKey {
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_Q,
        KEY_S,
        KEY_W,

        CONTROLLER_BUTTON_A,
        CONTROLLER_BUTTON_B,
        CONTROLLER_BUTTON_X,
        CONTROLLER_BUTTON_Y,
        CONTROLLER_BUTTON_SELECT,
        CONTROLLER_BUTTON_GUIDE,
        CONTROLLER_BUTTON_START,
        CONTROLLER_BUTTON_LEFTSTICK,
        CONTROLLER_BUTTON_RIGHTSTICK,
        CONTROLLER_BUTTON_LEFTSHOULDER,
        CONTROLLER_BUTTON_RIGHTSHOULDER,
        CONTROLLER_BUTTON_DPAD_UP,
        CONTROLLER_BUTTON_DPAD_DOWN,
        CONTROLLER_BUTTON_DPAD_LEFT,
        CONTROLLER_BUTTON_DPAD_RIGHT,
        CONTROLLER_BUTTON_MISC1,
        CONTROLLER_BUTTON_PADDLE1,
        CONTROLLER_BUTTON_PADDLE2,
        CONTROLLER_BUTTON_PADDLE3,
        CONTROLLER_BUTTON_PADDLE4,
        CONTROLLER_BUTTON_TOUCHPAD,
        CONTROLLER_AXIS_LEFTX,
        CONTROLLER_AXIS_LEFTY,
        CONTROLLER_AXIS_RIGHTX,
        CONTROLLER_AXIS_RIGHTY,
        CONTROLLER_AXIS_TRIGGERLEFT,
        CONTROLLER_AXIS_TRIGGERRIGHT,
        CONTROLLER_AXIS_MAX,

        MOUSE_X,
        MOUSE_Y,
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
        std::string ActionName;
        float Scale {1.f};
    };

    inline InputSource GetInputSourceFromKey(InputKey key) {
        switch(key) {
            case InputKey::KEY_A:
            case InputKey::KEY_B:
            case InputKey::KEY_C:
            case InputKey::KEY_D:
            case InputKey::KEY_E:
            case InputKey::KEY_Q:
            case InputKey::KEY_S:
            case InputKey::KEY_W:
                return InputSource::Keyboard;
            case InputKey::MOUSE_X:
            case InputKey::MOUSE_Y:
            case InputKey::MOUSE_MOVE_X:
            case InputKey::MOUSE_MOVE_Y:
            case InputKey::MOUSE_RIGHT:
            case InputKey::MOUSE_LEFT:
            case InputKey::MOUSE_MIDDLE:
                return InputSource::Mouse;
            case InputKey::CONTROLLER_BUTTON_A:
            case InputKey::CONTROLLER_BUTTON_B:
            case InputKey::CONTROLLER_BUTTON_X:
            case InputKey::CONTROLLER_BUTTON_Y:
            case InputKey::CONTROLLER_BUTTON_SELECT:
            case InputKey::CONTROLLER_BUTTON_GUIDE:
            case InputKey::CONTROLLER_BUTTON_START:
            case InputKey::CONTROLLER_BUTTON_LEFTSTICK:
            case InputKey::CONTROLLER_BUTTON_RIGHTSTICK:
            case InputKey::CONTROLLER_BUTTON_LEFTSHOULDER:
            case InputKey::CONTROLLER_BUTTON_RIGHTSHOULDER:
            case InputKey::CONTROLLER_BUTTON_DPAD_UP:
            case InputKey::CONTROLLER_BUTTON_DPAD_DOWN:
            case InputKey::CONTROLLER_BUTTON_DPAD_LEFT:
            case InputKey::CONTROLLER_BUTTON_DPAD_RIGHT:
            case InputKey::CONTROLLER_BUTTON_MISC1:
            case InputKey::CONTROLLER_BUTTON_PADDLE1:
            case InputKey::CONTROLLER_BUTTON_PADDLE2:
            case InputKey::CONTROLLER_BUTTON_PADDLE3:
            case InputKey::CONTROLLER_BUTTON_PADDLE4:
            case InputKey::CONTROLLER_BUTTON_TOUCHPAD:
            case InputKey::CONTROLLER_AXIS_LEFTX:
            case InputKey::CONTROLLER_AXIS_LEFTY:
            case InputKey::CONTROLLER_AXIS_RIGHTX:
            case InputKey::CONTROLLER_AXIS_RIGHTY:
            case InputKey::CONTROLLER_AXIS_TRIGGERLEFT:
            case InputKey::CONTROLLER_AXIS_TRIGGERRIGHT:
            case InputKey::CONTROLLER_AXIS_MAX:
                return InputSource::Gamepad;
            default:
                assert(false && "Invalid Input Source!");
                return InputSource::Unknown;
        }
    }

}