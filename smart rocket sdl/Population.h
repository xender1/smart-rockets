#pragma once
#include "Rocket.h"

class Population {
public:
	Population(SDL_Renderer* gRenderer, int popSize);
	~Population();

	void recreate(SDL_Renderer* gRenderer);

	void updateRockets();
	void renderRockets(SDL_Renderer* gRenderer);

	int getPopSize();

private:
	//will have vector of rockets but right now we start with one.
	vector<Rocket*> mPop;
	vector<Rocket*>::iterator it;

	int mPopSize;
};
