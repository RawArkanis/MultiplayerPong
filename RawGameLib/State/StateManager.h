#ifndef __RGL_STATE_MACHINE_H__
#define __RGL_STATE_MACHINE_H__

#include <map>

#include "State.h"

namespace RGL {

    class StateManager
    {
    public:
        StateManager();
        ~StateManager();

        void AddState(std::shared_ptr<State> state);
        void RemoveState(const std::string &name);

        std::shared_ptr<State> GetState(const std::string &name);

        bool ChangeState(const std::string &name);
    
        void Update(float delta);
    
    private:
        std::map<std::string, std::shared_ptr<State> > _stateMap;

        std::string _currentState;
    };

}

#endif
