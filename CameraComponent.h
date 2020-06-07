#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"
#include "ColliderComponent.h"
#include "FocusComponent.h"


class CameraComponent : public Component {

public:
	TransformComponent* transform;
	FocusComponent* focus;
	ColliderComponent* col;

	bool isLocked = true;

	CameraComponent() = default;

	void init() override {

		if (!entity->hasComponent<TransformComponent>()) {

			entity->addComponent<TransformComponent>();
		}

		if (!entity->hasComponent<FocusComponent>()) {

			entity->addComponent<FocusComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
		focus = &entity->getComponent<FocusComponent>();
		col = &entity->getComponent<ColliderComponent>();
	}

	void update() override {
		if (isLocked) {
			if (focus->isFocused) {

				Game::camera.x = transform->position.x - 400;
				Game::camera.y = transform->position.y - 320;

				if (Game::camera.x < 0) {
					Game::camera.x = 0;
				}
				if (Game::camera.y < 0) {
					Game::camera.y = 0;
				}
				if (Game::camera.x > Game::camera.w) {
					Game::camera.x = Game::camera.w;
				}
				if (Game::camera.y > Game::camera.h) {
					Game::camera.y = Game::camera.h;
				}
			}
		}
		else {
			if (Game::event.type == SDL_KEYDOWN) {

				switch (Game::event.key.keysym.sym)
				{
				case SDLK_UP:
					Game::camera.y -= 10;
					break;
				case SDLK_DOWN:
					Game::camera.y += 10;
					break;
				case SDLK_LEFT:
					Game::camera.x -= 10;
					break;
				case SDLK_RIGHT:
					Game::camera.x += 10;
					break;
				default:
					break;
				}
			}
		}
	}
};



