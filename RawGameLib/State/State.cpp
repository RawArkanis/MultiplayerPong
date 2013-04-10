#include "State.h"

namespace RGL {

    State::State(const std::string &name,
		const StartCallback &startCallback,
        const UpdateCallback &updateCallback,
        const StopCallback &stopCallback)
		: _name(name),
		_startCallback(startCallback),
		_updateCallback(updateCallback),
		_stopCallback(stopCallback)
    {
    }

    State::~State()
    {
    }

    std::string State::Name() const
    {
        return _name;
    }
    
    void State::start()
    {
        if (!_startCallback)
            _startCallback();
    }

    void State::update(float delta)
    {
        if (!_updateCallback)
            _updateCallback(delta);
    }

    void State::stop()
    {
        if (!_stopCallback)
            _stopCallback();
    }

}
