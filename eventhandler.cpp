#include "eventhandler.hpp"

void EventHandler::handleEvent(SDL_Event& ev, float &dollySpeed, float &panSpeed, float &truckSpeed) {
	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
			dollySpeed = 1.0f;
		if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
			dollySpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
			panSpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
			panSpeed = 1.0f;
		if (ev.key.keysym.sym == SDLK_q) truckSpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_e) truckSpeed = 1.0f;
	}
	if (ev.type == SDL_KEYUP) {
		if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) &&
				dollySpeed > 0)
			dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) &&
				dollySpeed < 0)
			dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) &&
				panSpeed < 0)
			panSpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) &&
				panSpeed > 0)
			panSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_q && truckSpeed < 0) truckSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_e && truckSpeed > 0) truckSpeed = 0.0f;
	}
}
