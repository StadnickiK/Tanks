#include "AssetManager.h"
#include "Components.h"
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "Menu.h"

assetManager::~assetManager(){}

void assetManager::addTexture(std::string id, const char* path) {
	try
	{
		textures.emplace(id, textureManager::loadTexture(path));
	}
	catch (const char* p)
	{
		std::cout << "addTexture: Pointer to file doesn't work //AssetManager.cpp" << std::endl;
	}
}

void assetManager::loadTextures(const char *path)
{
	std::ifstream textureFile;
	textureFile.open(path);
	std::string str;

	int a, b;
	while (!textureFile.eof()) {
		std::getline(textureFile, str);
		std::string name, txtPath;
		if (str[0] != '#') {
			for (int i = 0; i < str.length();i++) {
				if (str[i] != '=') {
					name += str[i];
					
				}else {
					
					i = str.length();
				}
			}
			a = str.find("[");
			b = str.find("]") - str.find("[") - 1;
			txtPath = str.substr(a + 1, b);
			name.erase(std::remove_if(name.begin(), name.end(), isspace), name.end());
			this->addTexture(name, txtPath.c_str());
		}
	}
}

SDL_Texture* assetManager::getTexture(std::string id) {
	return textures[id];
}

void assetManager::addFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font * assetManager::getFont(std::string id)
{
	return fonts[id];
}

void assetManager::createProjectile(vector2D position, vector2D velocity, double angle, int speed, std::string textID, const char* ownerTag){
	auto& projectile(man->addEntity());
	projectile.addComponent<TransformComponent>(position.x, position.y, 32, 32, 2);
	projectile.addComponent<SpriteComponent>(textID, false, angle);
	projectile.addComponent<ProjectileComponent>(speed, velocity);
	projectile.addComponent<ColliderComponent>("bullet", ownerTag);
	projectile.addGroup(Game::groupProjectiles);
	man->refresh();
}

void assetManager::createProjectile(vector2D position, vector2D velocity, double angle, int speed, std::string textID)
{
	auto& projectile(man->addEntity());
	projectile.addComponent<TransformComponent>(position.x, position.y, 32, 32, 2);
	projectile.addComponent<SpriteComponent>(textID, false, angle);
	projectile.addComponent<ProjectileComponent>(speed, velocity);
	projectile.addComponent<ColliderComponent>("bullet");
	projectile.addGroup(Game::groupProjectiles);
	man->refresh();
}

void assetManager::createProjectile(vector2D position, vector2D velocity, int speed, std::string textID) {
	auto& projectile(man->addEntity());
	projectile.addComponent<TransformComponent>(position.x, position.y, velocity, 2);
	projectile.addComponent<SpriteComponent>(textID, false);
	projectile.addComponent<BecomBulletComponent>(velocity.x, velocity.y);
	projectile.addComponent<borderControler>(640, 800, 2);
	projectile.addComponent<ColliderComponent>("bullet");
	projectile.addGroup(Game::groupProjectiles);
	man->refresh();
}