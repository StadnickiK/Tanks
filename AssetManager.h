#pragma once

#include <map>
#include <string>
#include "textureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "Game.hpp"
#include "SDL_ttf.h"
#include "Animation.h"
#include "Menu.h"

class assetManager {
public:
	assetManager(Manager* manager) : man(manager){}
	~assetManager();

	//texture managment
	void addTexture(std::string id, const char* path);
	void loadTextures(const char* path);
	SDL_Texture* getTexture(std::string id);

	void addFont(std::string id, std::string path, int fontSize);
	TTF_Font* getFont(std::string id);

	void createProjectile(vector2D position, vector2D velocity, double angle, int speed, std::string textID, const char * ownerTag);

	void createProjectile(vector2D position, vector2D velocity, double angle, int speed, std::string textID);

	//game objects

	void createProjectile(vector2D position, vector2D velocity, int range, int speed, std::string textID);

	void createProjectile(vector2D position, vector2D velocity, int speed, std::string textID);

private:

	Manager* man;
	std::map <std::string, SDL_Texture*> textures;
	std::map <std::string, TTF_Font*> fonts;
	int animIndex = 0;
};
