#pragma once
#include <SDL.h>
#include <cmath>

class Gene
{
public:
	static constexpr double MIN_GENE_VELOCITY = -3.0;
	static constexpr double MAX_GENE_VELOCITY = 3.0;

	Gene();
	~Gene();

	void randomize(); 

	double getVelX();
	double getVelY();
	Uint32 getTime();

private:
	double mVelX, mVelY;
	Uint32 mTime;
};
