#include "Gene.h"

Gene::Gene()
{
	//set random x y and time 
	mVelX = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mVelY = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mTime = rand() % 2000;
}

Gene::~Gene()
{
}

void Gene::randomize()
{
	//set random x y and time 
	mVelX = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mVelY = (MAX_GENE_VELOCITY - MIN_GENE_VELOCITY) * ((double)rand() / (double)RAND_MAX) + MIN_GENE_VELOCITY;
	mTime = rand() % 2000;
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
