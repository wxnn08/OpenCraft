#ifndef EVENT_HANDLER_HPP_
#define EVENT_HANDLER_HPP_

#include "abcg.hpp"

class EventHandler {
	public:
		void handleEvent(SDL_Event& ev, float &dollySpeed, float &panSpeed, float &truckSpeed);
};

#endif
