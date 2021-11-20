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


    float InputManager::GetActionValue(const std::string& actionName) {
        // TODO: This will need to be able to specify device indexes or sources or something later?
        auto& keys = _inputActionMapping[actionName];

        if (keys.empty()) {
            return 0.f;
        }

        // Get the largest value and return it
        float value = 0.f;
        InputKey theKey = InputKey::UNKNOWN;

        for (auto& key : keys) {
            // get the device
            auto device = GetInputSourceFromKey(key);

            // search for devices with that value
            for (auto& iDevice : _devices) {
                if (iDevice.Type == device) {
                    // check value of key
                    auto state = iDevice.StateFunc(iDevice.Index);
                    auto newVal = state[key].value;

                    if (std::abs(newVal) >= std::abs(value)) {
                        value = newVal;
                        theKey = key;
                    }
                }
            }
        }


        if (theKey == InputKey::UNKNOWN) {

            return 0.f;
        }

        // get the weight for that key
        float weight = 1.f;

        for (auto& action : _inputKeyMapping[theKey]) {
            if (action.ActionName == actionName) {
                weight = action.Scale;
                break;
            }
        }

        return value * weight;
    }

    void InputManager::MapInputToAction(InputKey key, const InputAction& action) {
        // TODO: Check for duplicates
        _inputKeyMapping[key].emplace_back(action);
        _inputActionMapping[action.ActionName].emplace_back(key);
    }

    void InputManager::UnmapInputFromAction(InputKey key, const std::string &actionName) {
        erase_if(_inputKeyMapping[key], [key, actionName](const InputAction& action) {
           return action.ActionName == actionName;
        });

        erase_if(_inputActionMapping[actionName], [key](const InputKey& inputKey) {
            return key == inputKey;
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


                if (newVal != oldVal) {
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

        auto& actions = _inputKeyMapping[key];
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