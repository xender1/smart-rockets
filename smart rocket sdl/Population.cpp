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
	for (vector<Rocket*>::const_iterator it = mMatePool.begin(); it != mMatePool.end(); ++it)
	{
		delete *it;
	}
	mPop.clear();
	mMatePool.clear();
}

void Population::recreate(SDL_Renderer * gRenderer)
{
	for (vector<Rocket*>::const_iterator it = mPop.begin(); it != mPop.end(); ++it)
	{
		delete *it;
	}
	for (vector<Rocket*>::const_iterator it = mMatePool.begin(); it != mMatePool.end(); ++it)
	{
		delete *it;
	}
	mPop.clear();
	mMatePool.clear();

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

void Population::checkCollision(SDL_Rect target)
{
	for (int i = 0; i < mPopSize; i++) {
		mPop.at(i)->checkCollision(target);
	}
}

bool Population::isComplete()
{
	int completeCount = 0;
	for (int i = 0; i < mPopSize; i++) {
		if (mPop.at(i)->isComplete()) {
			completeCount++;
		}
	}
	return completeCount == mPopSize;
}

void Population::evaluate(SDL_Rect target)
{
	for (int i = 0; i < mPopSize; i++) {
		mPop.at(i)->calculateFitness(target);
	}
}

void Population::createMatingPool(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < mPopSize; i++) {
		int inCount = mPop.at(i)->getFitnessScore() * 100;
		for (int j = 0; j < inCount; j++) {
			mMatePool.push_back(new Rocket(gRenderer, "rocket_mini.png"));
		}
	}
}

void Population::createNextGeneration()
{
	//get two random rockets

	//crossover dna

	//create new rocket from dna

	for (vector<Rocket*>::const_iterator it = mMatePool.begin(); it != mMatePool.end(); ++it)
	{
		delete *it;
	}
	mMatePool.clear();
}

int Population::getPopSize()
{
	return mPopSize;
}
