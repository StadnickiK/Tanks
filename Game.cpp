#pragma once
#include "Game.hpp"
#include <sstream>
#include "States.h"
#include "textureManager.h"
#include "AssetManager.h"
#include "map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ProjectilesComponent.h"
#include "ECS.h"
#include "Graph.h"
#include "miniMap.h"



bool canSh = true;
Map* map = nullptr;
Manager manager;
//miniMap* miniM;
Graph a;
Menu* menu = nullptr;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

assetManager* Game::assets = new assetManager(&manager);



								// auto [s³owo kluczowe] Zastêpczy typ zmiennej, który jest dedukowany na podstawie wartoœci jak¹ zmienna jest inicjalizowana.
auto& label(manager.addEntity());
     
auto& wall(manager.addEntity());
auto& enemy(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& crosshair(manager.addEntity());



auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& bullets(manager.getGroup(Game::groupProjectiles));
auto& special(manager.getGroup(Game::groupSpecial));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& players(manager.getGroup(Game::groupPlayers));

Game::Game ()
{}

Game::~Game()
{}

void Game::init(int xpos, int ypos)
{	
	
	dataLoader->loadInitFile(initData);	
	map = new Map("terrain", 3, 32);
	menu = new Menu(&manager, initData, map);
	int flags = 0;

	if (initData->fullscreen) {

		flags = SDL_WINDOW_FULLSCREEN;

	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		
		std::cout << "System ready..."<< std::endl;
		
		window = SDL_CreateWindow(initData->title, xpos, ypos, initData->width, initData->height, flags);
		
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	} else {
		isRunning = false;
	}


	if (TTF_Init() == -1) {
		std::cout << "Error : Failed to initialize SDL_TTF" << std::endl;
	}

	// assets - textureId , path
	assets->loadTextures("textures.txt");
	std::cout << "asset r" << std::endl;

	//assets->addTexture("miniM", "assets/miniM.png");
	
	assets->addFont("arial", "assets/arial.ttf", 16);
	assets->addFont("arial32", "assets/arial.ttf", 32);
	
	
	// ecs  
	map->getMapsList();

	enemy.addComponent<TransformComponent>(2);											// jeden argument SKALA
	enemy.addComponent<SpriteComponent>("enemy", true);
	enemy.addComponent<DeathControllerComponent>();
	enemy.addComponent<ColliderComponent>("enemy1");						// w nawiasie dodaje tag dla obiektu
	enemy.addComponent<HitPointComponent>(100);
	enemy.addComponent<borderControler>(640, 800, 2, 1);
	enemy.addGroup(groupPlayers);
	enemy.addComponent<StateMachineComponent>();
	enemy.addComponent<FocusComponent>();
	enemy.addComponent<CameraComponent>();

	enemy2.addComponent<TransformComponent>(250, 250, 2);											// jeden argument SKALA
	enemy2.addComponent<SpriteComponent>("enemy", true);
	enemy2.addComponent<DeathControllerComponent>();
	enemy2.addComponent<ColliderComponent>("enemy1");						// w nawiasie dodaje tag dla obiektu
	enemy2.addComponent<HitPointComponent>(100);
	enemy2.addComponent<borderControler>(640, 800, 2, 1);
	enemy2.addGroup(groupPlayers);
	enemy2.addComponent<RandomMovementComponent>();
	enemy2.addComponent<FocusComponent>();
	enemy2.addComponent<CameraComponent>();

	//map->loadMap("assets/map.txt", 25, 20);         // path, rozmiarX, rozmiarY  - MAPY, stara wersja
	/*
	if (initData->lastMap.c_str()) {
		map->loadMap(initData->lastMap.c_str());
		map->firstMap = initData->lastMap;
	}
	else {
		stopRunning();
	}
	//miniM = new miniMap(Game::renderer);

	/*
	enemy.addComponent<TransformComponent>(800, 800, 2);											// jeden argument SKALA
	enemy.addComponent<SpriteComponent>("enemy", true);
	enemy.addComponent<DeathControllerComponent>();
	enemy.addComponent<ColliderComponent>("enemy2");						// w nawiasie dodaje tag dla obiektu
	enemy.addComponent<HitPointComponent>(100);
	enemy.addComponent<borderControler>(640, 800, 2, 1);
	enemy.addGroup(groupPlayers);
	enemy.addComponent<RandomMovementComponent>();

	enemy.addComponent<TransformComponent>(1000, 150, 2);											// jeden argument SKALA
	enemy.addComponent<SpriteComponent>("enemy", true);
	enemy.addComponent<DeathControllerComponent>();
	enemy.addComponent<ColliderComponent>("enemy3");						// w nawiasie dodaje tag dla obiektu
	enemy.addComponent<HitPointComponent>(100);
	enemy.addComponent<borderControler>(640, 800, 2, 1);
	enemy.addGroup(groupPlayers);
	enemy.addComponent<RandomMovementComponent>();

	wall.addComponent<TransformComponent>(200.0f, 200.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/base-e.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);

	crosshair.addComponent<TransformComponent>(250, 250, 2);
	crosshair.addComponent<SpriteComponent>("assets/crosshair.png");
	crosshair.addComponent<ColliderComponent>("special");
	crosshair.addComponent<borderControler>(640, 800, 2, 2);
	crosshair.addComponent<CrosswiseMovementComponent>();
	crosshair.addGroup(groupSpecial);
	*/
	/*
	mMap.addComponent<TransformComponent>(320,400, 200, 160, 1);
	mMap.addComponent<VisibilityComponent>();
	mMap.addComponent<SetPositionComponent>(&camera, 320, 400);
	mMap.addGroup(groupSpecial);
	*/

	menu->mainMenu();
}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	
	switch (event.type) {

	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:
			break;
		case SDLK_f:
			
			a.newGraph();
			std::cout << "f" << std::endl;
			break;
		default:
			break;
		}

		break;
	case SDLK_UP:
		canSh = true;
		break;
	case SDL_QUIT:
		
		isRunning = false;
		break;

	default:
		break;

	}
}

void Game::update()
{	
	if (!menu->gameRunning) {
		this->isRunning = false;
	}
	for  (auto& c : bullets){
		for(auto& t : enemies){
			if (c != t) {
				if (c->getComponent<ColliderComponent>().tag == "bullet") {
					if (t->getComponent<ColliderComponent>().tag != c->getComponent<ColliderComponent>().ownerTag) {
						SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
						SDL_Rect tCol = t->getComponent<ColliderComponent>().collider;
						if (Collision::AABB(tCol, cCol)) {
							if (t->hasComponent<DeathControllerComponent>()) {
								t->getComponent<DeathControllerComponent>().isDead = true;
								std::cout << "dead " << t->getComponent<ColliderComponent>().tag;
							}
						}
					}
				}
			}
		}
	}
	/*
	std::stringstream ss;
	ss << "Player pos: " << playerPos;
	label.getComponent<ui_label>().setLabelText(ss.str(), "arial");
	*/
	manager.update();
	manager.refresh();
	//miniM->update();
}



void Game::render()
{	
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& b : bullets) {
		b->draw();
	}

	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	for (auto& s : special) {
		s->draw();
	}
	for (auto& c : colliders) {
		c->draw();
	}
	
	//label.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{	
	map->saveLastMap();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
