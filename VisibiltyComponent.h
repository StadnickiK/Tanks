#pragma once
#include "ECS.h"

class VisibilityComponent : public Component {

public:
	bool isVisible = true;
	bool newVisibility;
	VisibilityComponent() = default;

	VisibilityComponent(bool Visible) {
		isVisible = Visible;
	}

	void update() override {

		if (Game::event.type == SDL_KEYDOWN) {

			switch (Game::event.key.keysym.sym)
			{
			case SDLK_v:
				if (isVisible) {
					newVisibility = false;
				}
				if (isVisible == false) {
					newVisibility = true;
				}
				isVisible = newVisibility;
				break;
			default:
				break;
			}
		}
	}


};