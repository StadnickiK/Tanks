#pragma once

#include "Game.hpp"


class gameObject {

public:

	gameObject(const char* textureSheet, int x, int y);							//constructor
	~gameObject();																		//deconstructor


	void Update();
	void Render();


private:

	int xpos;
	int ypos;

	SDL_Texture* objectTexture;
	SDL_Rect srcR, destR;



};