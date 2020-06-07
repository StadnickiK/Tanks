#pragma once
#include <SDL.h>
#include "Components.h"
#include <vector>

class BecomBulletComponent : public Component {
private:
	TransformComponent	*transform;
	SpriteComponent *sprite;

	vector2D velocity;
	vector2D position;
	int height = 32;
	int width = 32;
	float posX, posY;
	char lastKey;
	

public:
	
	BecomBulletComponent() = default;
	BecomBulletComponent(float x, float y) {
		posX = x;
		posY = y;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		velocity.Zero();
	}

	

	void update() override {
		
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				lastKey = 'w';
				break;
			case SDLK_d:
				lastKey = 'd';
				break;
			case SDLK_a:
				lastKey = 'a';
				break;
			case SDLK_s:
				lastKey = 's';
				break;

			}
		}
		transform->position.x += posX;
		transform->position.y += posY;
		switch (lastKey)
		{
		case 'd':
			transform->velocity.x = 3;
			transform->velocity.y = 0;
			sprite->angle = NULL;
			break;
		case 'w':
			transform->velocity.x = 0;
			transform->velocity.y = -3;
			sprite->angle = -90;
			break;
		case 's':
			transform->velocity.y = 3;
			transform->velocity.x = 0;
			sprite->angle = 90;
			break;
		case 'a':
			transform->velocity.x = -3;
			transform->velocity.y = 0;
			sprite->angle = -180;
		default:
			break;
		}
	}

};



