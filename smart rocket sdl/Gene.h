#pragma once
#include <SDL.h>
#include <cmath>


class Gene
{
public:
	static constexpr double MIN_GENE_VELOCITY = -3.0;
	static constexpr double MAX_GENE_VELOCITY = 3.0;

	static const int MAX_GENE_TIME = 3000;

	Gene();
	Gene(double velX, double velY, Uint32 time);
	~Gene();

	void randomize(); 

	Gene crossover(Gene geneA, Gene geneB);

	double getVelX();
	double getVelY();
	Uint32 getTime();

private:
	double mVelX, mVelY;
	Uint32 mTime;
};
