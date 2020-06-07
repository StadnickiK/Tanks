
#include "SDL.h"
#include "Game.hpp"
#include <vector>
#include "Graph.h"



//y = ax+b
//y = ax^2+b^2+c

void Graph::swapValue(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Graph::setPixel(SDL_Surface * surface, int x, int y)
{
	if (x < surface->w && y < surface->h) {
		((Uint32*)surface->pixels)[y*surface->pitch / 4 + x] = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF);
	}
}

void Graph::drawLine(SDL_Surface * surface, int x, int y, int destX, int destY)
{	
	bool step = abs(destX - x) < abs(destY - y);

	if (step) {
		Graph::swapValue(x, y);
		Graph::swapValue(destX, destY);
	}
	if (destX < x) {
		Graph::swapValue(x, destX);
		Graph::swapValue(y, destY);
	}
	float error = 0.0f;
	float roundError = (float)abs(destY - y) / (destX - x);
	int ystep = (destY > y ? 1 : -1);
	int y0 = y;

	for (size_t i = x; i < destX; i++)
	{		
		if (step) {
			Graph::setPixel(surface, y0, i);
		}
		else
		{
			Graph::setPixel(surface, i, y0);
		}
		error += roundError;
		if (error >= 0.5f) {
			y0+=ystep;
			error -= 1.0f;
		}
	}
}

void Graph::pow(float* number, int* power)
{	
	float v = *number;

	for (int i = 1; i < *power;i++) {
		*number *= v;
	}
}

float Graph::posY(SDL_Surface* surface, int ile, float x)
{	
	float y = 0;
	float p = 0;
	int z = 1, vec = 0;
	
	std::cout <<"ile "<<ile << std::endl;

	for (int i = ile;i > 0;i--) {
		p = x - (float)surface->w/2;
			z = Graph::tab[vec];
			if (ile != 1) {
				Graph::pow(&p, &i);
			}
			y += p * z;
			std::cout << "y " << y << std::endl;
			vec++;
	}
	y += Graph::tab[ile];
	return y;
}

void Graph::newGraph()
{
	int ile = 0;
	float a = 0;
	SDL_Surface* miniM = SDL_CreateRGBSurface(0, 250, 250, 32, 0, 0, 0, 0);
	
	Uint32 *pixels = (Uint32 *)miniM->pixels;

	std::cout << "Podaj stopieñ funcji: " << std::endl;
	std::cin >> ile;
	std::cout << "Podaj liczbe: " << std::endl;
	for (int i = ile + 1;i > 0; i--) {
		std::cin >> a;
		Graph::tab.push_back(a);
	}
	
	int y = miniM->h/2;
	int y2 = 0;

	Graph::drawLine(miniM, 0, miniM->h/2, miniM->w, miniM->h/2);
	Graph::drawLine(miniM, miniM->w / 2, 0, miniM->w/2, miniM->h);

	for(float x = miniM->w / 2; x<miniM->w; x++){
		y2 = Graph::posY(miniM, ile, x) + miniM->h/2;
		Graph::drawLine(miniM, x, y, x+1, y2);
		y = Graph::posY(miniM, ile, x) + miniM->h / 2;
	}

	for (float x = miniM->w/2; x>0; x--) {
		y2 = Graph::posY(miniM, ile, x) + miniM->h / 2;
		Graph::drawLine(miniM, x, y, x + 1, y2);
		y = Graph::posY(miniM, ile, x) + miniM->h / 2;
	}

	float z = 1;
	std::cout<<Graph::posY(miniM, ile, z)<<std::endl;
	SDL_SaveBMP(miniM, "assets/test.bmp");
	SDL_FreeSurface(miniM);
}
