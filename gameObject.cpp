#include "gameObject.h"
#include "textureManager.h"


gameObject::gameObject(const char* texturesheet, int x, int y) {

	
	objectTexture = textureManager::loadTexture(texturesheet);

	xpos = x;
	ypos = y;

}



void gameObject::Update() {

	xpos++;
	ypos++;

	srcR.h = 32;
	srcR.w = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.x = xpos;
	destR.y = ypos;
	destR.h = srcR.h;
	destR.w = srcR.w;



}


void gameObject::Render() {

	SDL_RenderCopy(Game::renderer, objectTexture, &srcR, &destR);

}

