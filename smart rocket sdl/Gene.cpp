#include "Gene.h"

Gene::Gene()
{
	//set random x y and time 
	mVelX = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mVelY = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mTime = rand() % MAX_GENE_TIME;
}

Gene::~Gene()
{
}

Gene::Gene(double velX, double velY, Uint32 time) {
	mVelX = velX;
	mVelY = velY;
	mTime = time;
}

void Gene::randomize()
{
	//set random x y and time 
	mVelX = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mVelY = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mTime = rand() % MAX_GENE_TIME;
}

Gene Gene::crossover(Gene geneA, Gene geneB)
{
	Gene newGenes;

	return newGenes;
}

double Gene::getVelX()
{
	return mVelX;
}

double Gene::getVelY()
{
	return mVelY;
}

Uint32 Gene::getTime()
{
	return mTime;
}
