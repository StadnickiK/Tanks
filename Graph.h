#pragma once



class Graph {

	const char* func;
	float* y;
	
	

public:

	
	std::vector <float> tab;

	void loadFunction(const char* function);
	void loadFunction();

	//y = ax+b
	//y = ax^2+b^2+c

	void swapValue(float* a, float* b);

	void swapValue(int & a, int & b);
	void setPixel(SDL_Surface * surface, int x, int y);
	void drawLine(SDL_Surface * surface, int x, int y, int destX, int destY);
	void pow(float *number, int* power);
	float posY(SDL_Surface * surface, int ile, float x);
	float posY(int ile, float x);
	void newGraph();

};


