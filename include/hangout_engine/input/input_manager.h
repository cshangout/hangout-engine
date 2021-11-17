#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <unordered_set>

#include "input_key.h"
#include "input_devices.h"

namespace HE {
    class InputManager {
        friend class Game;
    public:
        using ActionCallbackFunc = std::function<bool(InputSource, int, float)>;

        struct ActionCallback {
            std::string Ref;
            ActionCallbackFunc Func;
        };

    private:
        struct ActionEvent {
            std::string ActionName;
            InputSource Source;
            int SourceIndex;
            float Value;
        };

    public:
        InputManager();
        ~InputManager();

        void RegisterActionCallback(const std::string& actionName, const ActionCallback& callback);
        void RemoveActionCallback(const std::string& actionName, const std::string& callbackRef);

        void MapInputToAction(InputKey key, const InputAction& action);
        void UnmapInputFromAction(InputKey key, const std::string& actionName);

        void RegisterDevice(const InputDevice& device);
        void RemoveDevice(InputDeviceType source, int inputIndex);

    private:
        void processInput();
        std::vector<ActionEvent> generateActionEvent(int deviceIndex, InputKey key, float newVal);
        void propagateActionEvent(const ActionEvent& event);
    private:
        bool _active { true };
        std::unordered_map<InputKey, std::vector<InputAction>> _inputActionMapping;
        std::unordered_map<std::string, std::vector<ActionCallback>> _actionCallbacks;

        std::vector<InputDevice> _devices;
    };
}

