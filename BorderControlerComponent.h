#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"

class borderControler : public Component {

	int h, w;
	TransformComponent *transform;
	Entity *to;
	int sc = 1;
	int mod = 0;
public:

	borderControler(int height, int width){
		h = height;
		w = width;
	}
	borderControler(int height, int width, int scale) {
		h = height;
		w = width;
		sc = scale;
	}

	borderControler(int height, int width, int scale, int mode) {
		h = height;
		w = width;
		mod = mode;
		sc = scale;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		to = entity;
	}

	void update() override
	{	
		switch (mod) {
		case 0:
			if (transform->position.x > w*sc)
			{
				std::cout << "x>w" << std::endl;
				to->destroy();
			}
			if (transform->position.x < -32)
			{
				to->destroy();
				std::cout << "x<0" << std::endl;
			}
			if (transform->position.y > h*sc)
			{
				to->destroy();
				std::cout << "y>h" << std::endl;
			}
			if (transform->position.y < -32)
			{
				to->destroy();
				std::cout << "y<0" << std::endl;
			}
			break;
		case 1:
			if (transform->position.x > w*sc)
			{
				transform->position.x = 1;
			}
			if (transform->position.x < -32)
			{
				transform->position.x = w*sc - 1;
			}
			if (transform->position.y > h*sc)
			{
				transform->position.y = 1;
			}
			if (transform->position.y < -32)
			{
				transform->position.y = h*sc - 1;
			}
			break;
		case 2:
			if ((transform->position.x > w*sc +30) || (transform->position.x < -2) || (transform->position.y > h*sc - 30) || (transform->position.y < -2)) {
				if (transform->velocity.x == 1 && transform->velocity.y == 1 ||
					transform->velocity.y == 1 && transform->velocity.x == -1 && transform->position.x>-2 ||
					transform->velocity.x == -1 && transform->velocity.y == -1 ||
					transform->velocity.y == -1 && transform->velocity.x == 1 && transform->position.x<w*sc) {
					transform->velocity.y *= -1;
				}
				else {
					transform->velocity.x *= -1;
				}
				
			}
			break;
		}
	}
};