#pragma once
#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"
#include "Collision.h"

class CollisionDetectionComponent : public Component {


public:

	SDL_Rect collider;
	std::string tag;

	
	ColliderComponent* coll;

	void init() override {

		if (!entity->hasComponent<ColliderComponent>()) {

			entity->addComponent<ColliderComponent>("tag");
		}
		coll = &entity->getComponent<ColliderComponent>();

	}

	void update() override {

		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);									// aktualizuje polorzenie collider'a , collider.x to int a position.x to float, static_cast konwertuje
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;					// zasieg kolizji

		for (auto cc : Game::colliders) {

			Collision::AABB(*coll, *cc);
		}

	}

};
