#pragma once
#ifndef  Game_hpp
#define Game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Menu.h"
#include "AssetManager.h"
#include "BootLoader.h"


class assetManager;
class ColliderComponent;

class Game {

private:
	/*
	ColliderComponent* getColliderComponent(Entity* entity) {
		if (entity->hasComponent<ColliderComponent>()) {
			ColliderComponent* collider = &entity->getComponent<ColliderComponent>();
			return collider;
		}
		return nullptr;
	}
	*/
public:
	Game();
	~Game();
	void init(int xpos, int ypos);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; };
	void stopRunning() { isRunning = false; }

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static assetManager* assets;

	enum groupLabels : std::size_t {
		groupMap,
		groupProjectiles,
		groupPlayers,
		groupEnemies,
		groupSpecial,
		groupColliders
	};
	SDL_Window *window;
	Data* initData = new Data("Tanks", 800, 640, false, "x");
private:
	BootLoader* dataLoader = new BootLoader();
	int cnt = 0;
	bool isRunning;
};

#endif // ! Game_hpp
