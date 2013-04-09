#include "StateManager.h"

namespace RGL {

    StateManager::StateManager()
        : _currentState("") 
    {
    }

    StateManager::~StateManager()
    {
        _stateMap.clear();
    }

    void StateManager::addState(std::shared_ptr<State> state)
    {
        _stateMap[state->getName()] = state;
    }

    void StateManager::removeState(const std::string &name)
    {
        _stateMap.erase(name);
    }

    std::shared_ptr<State> StateManager::getState(const std::string &name)
    {
        return _stateMap[name];
    }
 
    bool StateManager::changeState(const std::string &name)
    {
        if (!_stateMap[name])
            return false;

        if (_currentState != "")
            _stateMap[_currentState]->stop();

        _currentState = name;

        if (_currentState != "")
            _stateMap[_currentState]->start();

        return true;
    }

    void StateManager::update(float delta)
    {
        if (_currentState != "")
            _stateMap[_currentState]->update(delta);
    }

}
