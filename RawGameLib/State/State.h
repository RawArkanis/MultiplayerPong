#ifndef __RGL_STATE_H__
#define __RGL_STATE_H__

#include <functional>

#include "../Common.h"

namespace RGL {

    typedef std::function<void()> StartCallback;
    typedef std::function<void(float)> UpdateCallback;
    typedef std::function<void()> StopCallback;

    class State
    {
    public:
        State(const std::string &name, const StartCallback &startCallback = nullptr,
            const UpdateCallback &updateCallback = nullptr,
            const StopCallback &stopCallback = nullptr);
        ~State();
    
        std::string getName();
    
        void start();
        void update(float delta);
        void stop();
    
    private:
        std::string _name;

        StartCallback _startCallback;
        UpdateCallback _updateCallback;
        StopCallback _stopCallback;
    };

}

#endif
