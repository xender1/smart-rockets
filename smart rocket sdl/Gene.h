#pragma once
#include "main.h"


class Gene
{
public:
	Gene();
	Gene(double velX, double velY, Uint32 time);
	~Gene();

	void setGeneValues(double velX, double velY, Uint32 time);
	void randomize(); 

	double getVelX();
	double getVelY();
	Uint32 getTime();

private:
	double mVelX, mVelY;
	Uint32 mTime;
};
