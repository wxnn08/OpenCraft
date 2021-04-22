#ifndef EVENT_HANDLER_HPP_
#define EVENT_HANDLER_HPP_

#include "abcg.hpp"
#include "camera.hpp"

class EventHandler {
	public:
		void handleEvent(SDL_Event& ev, Camera *camera);
};

#endif
