#include "Population.h"

Population::Population(SDL_Renderer * gRenderer, int popSize)
{
	mPopSize = popSize;
	for (int i = 0; i < mPopSize; i++) {
		//Rocket* newRocket = new Rocket(gRenderer, "rocket_mini.png");
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png"));
	}
	mGenNum = 0; mMaxFit = 0;
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
	mGenNum = 0; mMaxFit = 0;

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
		vector<Gene> newDna;
		for (int j = 0; j < 5; j++) {
			Gene newGene(0, -3, 3000);
			newDna.push_back(newGene);
		}
		//mPop.push_back(new Rocket(gRenderer, "rocket_mini.png"));
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png", newDna));
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
	int currFit = 0;
	for (int i = 0; i < mPopSize; i++) {
		currFit = mPop.at(i)->calculateFitness(target);
		if (currFit > mMaxFit) { mMaxFit = currFit; }
	}
}

void Population::createMatingPool(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < mPopSize; i++) {
		int inCount = mPop.at(i)->getFitnessScore() * 100;
		if (mPop.at(i)->getHitTarget()) { inCount += 200; }
		cout << mPop.at(i)->getFitnessScore() << " " << inCount << endl;
		for (int j = 0; j < inCount; j++) {
			mMatePool.push_back(new Rocket(gRenderer, "rocket_mini.png", mPop[i]->getDna()));
		}
	}
}

void Population::createNextGeneration(SDL_Renderer * gRenderer)
{

	mGenNum++;

	for (vector<Rocket*>::const_iterator it = mPop.begin(); it != mPop.end(); ++it)
	{
		delete *it;
	}
	mPop.clear();

	for (int i = 0; i < mPopSize; i++) {
		//get two random rockets dna from mating pool
		int index = rand() % mMatePool.size();
		vector<Gene> parentA = mMatePool[index]->getDna();
		index = rand() % mMatePool.size();
		vector<Gene> parentB = mMatePool[index]->getDna();

		vector<Gene> newDna;
		
		//split on mid points
		int midPoint = rand() % parentA.size();
		for (int j = 0; j < parentA.size(); j++) {
			//Gene newGene((parentA[j].getVelX() + parentB[j].getVelX()) / 2, (parentA[j].getVelY() + parentB[j].getVelY()) / 2,
			//	(parentA[j].getTime() + parentB[j].getTime()) / 2);
			
			if (j > midPoint) {
				Gene newGene(parentA[j].getVelX(), parentA[j].getVelY(), parentA[j].getTime());
				newDna.push_back(newGene);
			}
			else {
				Gene newGene(parentB[j].getVelX(), parentB[j].getVelY(), parentB[j].getTime());
			//Gene newGene(parentA[j].getVelX(), parentA[j].getVelY(), parentA[j].getTime());
				newDna.push_back(newGene);
			}
		}
		//create new rocket from dna in population
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png", newDna));

	}

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

vector<Rocket*> Population::getPopluation()
{
	return mPop;
}
