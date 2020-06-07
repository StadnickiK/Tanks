#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"

class FocusComponent : public Component {



public:
	bool isFocused = false;
	bool newFocus;
	FocusComponent() = default;

	FocusComponent(bool Focused) {
		isFocused = Focused;
	}

	void update() override {

		if (Game::event.type == SDL_KEYDOWN) {

			switch (Game::event.key.keysym.sym)
			{
			case SDLK_x:
				if (isFocused) {
					newFocus = false;
				}
				if (isFocused == false) {
					newFocus = true;
				}
				isFocused = newFocus;
				break;
			default:
				break;
				}
				
			}
		}
		
	
};