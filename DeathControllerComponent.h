#pragma once

#include "Game.hpp"
#include "Components.h"
#include "ECS.h"
#include "ColliderComponent.h"
#include "FocusComponent.h"


#include <cstdlib>
#include <ctime>
#include <cstdio>

class DeathControllerComponent : public Component {

public:
	TransformComponent* transform;
	FocusComponent* focus;
	ColliderComponent* coll;

	bool isDead = false;
	const char* destBy;
	int i;
	void init() override {

		srand(time(NULL));
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		if (!entity->hasComponent<ColliderComponent>()) {
			entity->addComponent<ColliderComponent>("placeholder");
		}
		transform = &entity->getComponent<TransformComponent>();
		focus = &entity->getComponent<FocusComponent>();
		coll = &entity->getComponent<ColliderComponent>();
	}

	void update() override {

		if (isDead) {
			i++;
			if (i >= 120){
				transform->position.x = rand() % 1200 + 5;
				transform->position.y = rand() % 1200 + 5;
				isDead = false;
				i = 0;
			}
			/*else {
				if (coll) {
					if (coll->tag == destBy) {
						if (focus) {
							focus->isFocused = true;
						}
					}
					else {
						if (focus) {
							focus->isFocused = false;
						}
					}
				}
			*/}
		//}
	}

};