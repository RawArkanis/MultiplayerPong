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

        void addState(std::shared_ptr<State> state);
        void removeState(const std::string &name);

        std::shared_ptr<State> getState(const std::string &name);

        bool changeState(const std::string &name);
    
        void update(float delta);
    
    private:
        std::map<std::string, std::shared_ptr<State> > _stateMap;

        std::string _currentState;
    };

}

#endif
