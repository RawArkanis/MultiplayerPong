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

    void StateManager::AddState(std::shared_ptr<State> state)
    {
        _stateMap[state->Name()] = state;
    }

    void StateManager::RemoveState(const std::string &name)
    {
        _stateMap.erase(name);
    }

    std::shared_ptr<State> StateManager::GetState(const std::string &name)
    {
        return _stateMap[name];
    }
 
    bool StateManager::ChangeState(const std::string &name)
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

    void StateManager::Update(float delta)
    {
        if (_currentState != "")
            _stateMap[_currentState]->update(delta);
    }

}
