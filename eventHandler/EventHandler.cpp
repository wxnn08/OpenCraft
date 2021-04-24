#include "EventHandler.hpp"

void EventHandler::handleEvent(SDL_Event& ev, Camera *camera) {
	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
			camera->m_dollySpeed = 8.0f;
		if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
			camera->m_dollySpeed = -8.0f;
		if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
			camera->m_panSpeed = -2.0f;
		if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
			camera->m_panSpeed = 2.0f;
		if (ev.key.keysym.sym == SDLK_q) 
			camera->m_truckSpeed = -5.0f;
		if (ev.key.keysym.sym == SDLK_e) 
			camera->m_truckSpeed = 5.0f;
	}
	if (ev.type == SDL_KEYUP) {
		if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) && camera->m_dollySpeed > 0)
			camera->m_dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) && camera->m_dollySpeed < 0)
			camera->m_dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) && camera->m_panSpeed < 0)
			camera->m_panSpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) && camera->m_panSpeed > 0)
			camera->m_panSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_q && camera->m_truckSpeed < 0) 
			camera->m_truckSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_e && camera->m_truckSpeed > 0) 
			camera->m_truckSpeed = 0.0f;
	}
}
