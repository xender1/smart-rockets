#include "Population.h"

Population::Population(SDL_Renderer * gRenderer, int popSize)
{
	mPopSize = popSize;
	for (int i = 0; i < mPopSize; i++) {
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
		vector<Gene> newDna;
		for (int j = 0; j < 5; j++) {
			Gene newGene(0, -3, 3000);
			newDna.push_back(newGene);
		}
		mPop.push_back(new Rocket(gRenderer, "rocket_mini.png", newDna));
	}
}

void Population::updateRockets(vector<CollisionObject*> collisionObjects)
{
	for (int i = 0; i < mPopSize; i++) {
		//Rocket* rocket = mPop.at(i);
		mPop.at(i)->move(collisionObjects);
	}
}

void Population::renderRockets(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < mPopSize; i++) {
		mPop.at(i)->render(gRenderer);
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
	double currFit = 0.0;
	for (int i = 0; i < mPopSize; i++) {
		currFit = mPop.at(i)->calculateFitness(target);
		if (currFit > mMaxFit) { mMaxFit = currFit; }
	}
}

void Population::createMatingPool(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < mPopSize; i++) {
		int inCount = (int)mPop.at(i)->getFitnessScore() * 100;
		if (mPop.at(i)->getHitTarget()) { inCount += 200; }
		//cout << mPop.at(i)->getFitnessScore() << " " << inCount << endl;
		for (int j = 0; j < inCount; j++) {
			mMatePool.push_back(new Rocket(mPop[i]->getDna()));
		}

		if (mMatePool.size() == 0) {
			//mating pool is current pop
			for (int i = 0; i < mPopSize; i++) {
				mMatePool.push_back(new Rocket(mPop[i]->getDna()));
			}
		}
	}
}

void Population::createNextGeneration(SDL_Renderer * gRenderer)
{

	mGenNum++;

	//for (vector<Rocket*>::const_iterator it = mPop.begin(); it != mPop.end(); ++it)
	//{
	//	delete *it;
	//}
	//mPop.clear();

	for (int i = 0; i < mPopSize; i++) {
		//get two random rockets dna from mating pool
		vector<Gene> parentA = mMatePool[rand() % mMatePool.size()]->getDna();
		vector<Gene> parentB = mMatePool[rand() % mMatePool.size()]->getDna();

		vector<Gene> newDna;
		
		//split on mid points
		unsigned int midPoint = rand() % parentA.size();
		for (unsigned int j = 0; j < parentA.size(); j++) {
			//Gene newGene((parentA[j].getVelX() + parentB[j].getVelX()) / 2, (parentA[j].getVelY() + parentB[j].getVelY()) / 2,
			//	(parentA[j].getTime() + parentB[j].getTime()) / 2);
			Gene newGene;
			if (j > midPoint) {
				newGene.setGeneValues(parentA[j].getVelX(), parentA[j].getVelY(), parentA[j].getTime());
			}
			else {
				newGene.setGeneValues(parentB[j].getVelX(), parentB[j].getVelY(), parentB[j].getTime());
			}
			//chance gene is brand new
			if (rand() % 100 < MUTATION_SINGLE_GENE_CHANCE) {
				newGene.randomize();
				cout << "mutation of single gene" << endl;
			}

			newDna.push_back(newGene);
		}
		//create new rocket from dna in population, chance brand new dna is created
		if (rand() % 100 < MUTATION_DNA_SEQUENCE_CHANCE) {
			cout << "mutation of entire gene sequence" << endl;
			mPop[i]->recreate(newDna);
		}
		else {
			mPop[i]->recreate(newDna);
		}
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
