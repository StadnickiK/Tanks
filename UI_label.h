#pragma once
#include "ECS.h"
#include "AssetManager.h"
#include "textureManager.h"
#include "Game.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
#include "string"

class ui_label : public Component{

public:
	ui_label(int xPos, int yPos, std::string text, std::string font, SDL_Color& color) : 
		labelText(text), lFont(font), tColor(color) {
	
		pos.x = xPos;
		pos.y = yPos;
		setLabelText(labelText, lFont);
	}
	ui_label(SDL_Rect data, std::string text, std::string font, SDL_Color& color) :
		labelText(text), lFont(font), tColor(color), pos(data) {
		TTF_Font* f = (Game::assets->getFont(font));
		int x, y;
		if (TTF_SizeText(f, text.c_str(), &x, &y) != 1) {
		}
		else {
			std::cout << "Failed to measure the height and width of text /ui_label" << std::endl;
		}
		pos.x = pos.x + pos.w / 2 - x/2;
		pos.y = pos.y + pos.h / 2 - y/2;
		setLabelText(labelText, lFont);
	}
	~ui_label(){}

	void setLabelText(std::string text, std::string font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), tColor);
		lText = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf); 

		SDL_QueryTexture(lText, nullptr, nullptr, &pos.w, &pos.h);
	}

	std::string getLabelText() {
		return labelText;
	}

	void draw() override{
		SDL_RenderCopy(Game::renderer, lText, nullptr, &pos);
	}

private:
	SDL_Rect pos;
	std::string labelText;
	std::string lFont;
	SDL_Color tColor;
	SDL_Texture* lText;
};