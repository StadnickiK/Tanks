#pragma once


struct Animation {

	int index;
	int frames; 
	int speed;

	Animation() {}
	Animation(int Index, int Frames, int Speed){
		index = Index;
		frames = Frames;
		speed = Speed;
	}
};
