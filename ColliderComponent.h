#pragma once
#include <string>
#include <SDL.h>
#include "TransformComponent.h"
#include "Collision.h"
#include "textureManager.h"

class ColliderComponent : public Component {
private:
	std::map<std::string, SDL_Rect*> colliders;
public:

	SDL_Rect collider;
	const char* tag;
	const char* ownerTag = NULL;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;
	ColliderComponent* to;
	Entity* ent;

	//ColliderComponent() = default;								//collider nie mo¿e mieæ defaultu bez TAGU !!!!!!
	ColliderComponent(const char* t) {
		collider.x = 0;
		collider.y = 0;
		collider.w = 0;
		collider.h = 0;
		tag = t;
	}

	ColliderComponent(const char* t, int x, int y, int size){
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = collider.w = size;
	}

	ColliderComponent(const char* t, const char* owner) {
		collider.x = 0;
		collider.y = 0;
		collider.w = 0;
		collider.h = 0;
		tag = t;
		ownerTag = owner;
	}

	void init() override {

		if (!entity->hasComponent<TransformComponent>()) {

			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		to = &entity->getComponent<ColliderComponent>();
		ent = entity;
		
		tex = textureManager::loadTexture("assets/colltex.png");
		srcR = { 0 ,0,32,32 };
		destR = { collider.x, collider.y, collider.w, collider.h };
		
		
	}

	void update() override {

		if (tag != "terrain") {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);									// aktualizuje polorzenie collider'a , collider.x to int a position.x to float, static_cast konwertuje
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;					// zasieg kolizji
		}

		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
		

	}

	void draw() override {

		textureManager::draw(tex, srcR, destR, NULL, SDL_FLIP_NONE);
	
	}

	void addCollider(std::string tag, SDL_Rect* rect) {
		if (rect) {
			if (!colliders.count(tag)) {
				colliders.emplace(tag, rect);
			}
		}
	}

	SDL_Rect* getCollider(std::string tag) {
		return colliders[tag];
	}

};
