#pragma once


//const char *title, int xpos, int ypos, int width, int height, bool fullscreen

struct Data
{	
	Data() {
		title = "Tanks";
		width = 800;
		height = 640;
		fullscreen = false;
		lastMap = "x";
	}
	Data(const char* Title, int Width, int Height, bool Fullscreen, const char* mapName) : lastMap(mapName) {
		title = Title;
		width = Width;
		height = Height;
		fullscreen = Fullscreen;
	}
	const char* title;
	int width;
	int height;
	bool fullscreen;
	std::string lastMap;
};