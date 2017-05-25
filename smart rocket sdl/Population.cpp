#include "Population.h"

Population::Population(SDL_Renderer * gRenderer, int popSize)
{
	mPopSize = popSize;
	for (int i = 0; i < mPopSize; i++) {
		//Rocket* newRocket = new Rocket(gRenderer, "rocket_mini.png");
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png"));
	}
}

Population::~Population()
{
	for (vector<Rocket*>::const_iterator it = mPop.begin(); it != mPop.end(); ++it)
	{
		delete *it;
	}
	mPop.clear();
}

void Population::recreate(SDL_Renderer * gRenderer)
{
	for (vector<Rocket*>::const_iterator it = mPop.begin(); it != mPop.end(); ++it)
	{
		delete *it;
	}
	mPop.clear();

	for (int i = 0; i < mPopSize; i++) {
		//Rocket* newRocket = new Rocket(gRenderer, "rocket_mini.png");
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png"));
	}
}

void Population::updateRockets()
{
	for (int i = 0; i < mPopSize; i++) {
		//Rocket* rocket = mPop.at(i);
		mPop.at(i)->move();
	}
}

void Population::renderRockets(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < mPopSize; i++) {
		mPop.at(i)->render(gRenderer);
	}
}

int Population::getPopSize()
{
	return mPopSize;
}
