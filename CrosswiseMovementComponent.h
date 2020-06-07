#pragma once

#pragma once


#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>




class CrosswiseMovementComponent : public Component {

	public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		transform->velocity.x = 1;
		transform->velocity.y = 1;
	}

};