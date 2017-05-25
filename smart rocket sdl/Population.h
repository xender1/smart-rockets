#pragma once
#include "Rocket.h"

class Population {
public:
	Population(SDL_Renderer* gRenderer, int popSize);
	~Population();

	void recreate(SDL_Renderer* gRenderer);

	void updateRockets();
	void renderRockets(SDL_Renderer* gRenderer);

	void checkCollision(SDL_Rect target);

	bool isComplete();

	//evaluates rocket population at end and sets rockets fitness scores based on target
	void evaluate(SDL_Rect target);
	//populates mating pool from fitness values of pop
	void createMatingPool(SDL_Renderer * gRenderer);
	void createNextGeneration(SDL_Renderer * gRenderer);

	int getPopSize();
	double getMaxFitScore() { return mMaxFit; }
	int getGenerationNum() { return mGenNum; }

	vector<Rocket*> getPopluation();

private:
	//will have vector of rockets but right now we start with one.
	vector<Rocket*> mPop;
	vector<Rocket*>::iterator it;

	//mating pool
	vector<Rocket*> mMatePool;

	int mPopSize;
	int mMatePoolSize;

	double mMaxFit;
	int mGenNum;
};
