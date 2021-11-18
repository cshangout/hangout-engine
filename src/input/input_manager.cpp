#include <hangout_engine/input/input_manager.h>
#include <iostream>

namespace HE {
    InputManager::InputManager() {}

    InputManager::~InputManager() {}

    void InputManager::RegisterActionCallback(const std::string &actionName, const InputManager::ActionCallback& callback) {
        _actionCallbacks[actionName].emplace_back(callback);
    }

    void InputManager::RemoveActionCallback(const std::string &actionName, const std::string& callbackRef) {
        erase_if(_actionCallbacks[actionName], [callbackRef](const ActionCallback& callback) {
            return callback.Ref == callbackRef;
        });
    }

    void InputManager::MapInputToAction(InputKey key, const InputAction& action) {
        // TODO: Check for duplicates
        _inputActionMapping[key].emplace_back(action);
    }

    void InputManager::UnmapInputFromAction(InputKey key, const std::string &actionName) {
        erase_if(_inputActionMapping[key], [key, actionName](const InputAction& action) {
           return action.ActionName == actionName;
        });
    }

    void InputManager::processInput() {
        std::vector<ActionEvent> events{};

        for (auto& device : _devices) {
            // get new state
            auto newState = device.StateFunc(device.Index);

            for (auto& keyState : newState) {
                InputKey key = keyState.first;
                float newVal = keyState.second.value;
                float oldVal = device.CurrentState[key].value;

                if (oldVal != newVal) {
                    auto generatedEvents = generateActionEvent(device.Index, keyState.first, keyState.second.value);
                    events.insert(events.end(), generatedEvents.begin(), generatedEvents.end());

                    device.CurrentState[key].value = newVal;
                }
            }
        }

        // propagate action events
        for (auto& event : events) {
            propagateActionEvent(event);
        }
    }

    std::vector<InputManager::ActionEvent> InputManager::generateActionEvent(int deviceIndex, InputKey key, float newVal) {
        std::vector<ActionEvent> events {};

        auto& actions = _inputActionMapping[key];
        InputSource source = GetInputSourceFromKey(key);

        for (auto& action : actions) {
            events.emplace_back(ActionEvent {
                .ActionName = action.ActionName,
                .Source = source,
                .SourceIndex = deviceIndex,
                .Value = newVal * action.Scale
            });
        }
        return events;
    }

    void InputManager::propagateActionEvent(const InputManager::ActionEvent& event) {
        // we use a reverse iterator here to go through the vector backwards
        for(auto action = _actionCallbacks[event.ActionName].rbegin(); action != _actionCallbacks[event.ActionName].rend(); action++) {
            if ((*action).Func(event.Source, event.SourceIndex, event.Value)) {
                break;
            }
        }
    }

    void InputManager::RegisterDevice(const InputDevice& device) {
        _devices.emplace_back(device);
    }

    void InputManager::RemoveDevice(InputSource type, int inputIndex) {
        erase_if(_devices, [type, inputIndex](const InputDevice& device) {
            return device.Type == type && device.Index == inputIndex;
        });
    }
}