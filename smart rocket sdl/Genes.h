#pragma once
#include "main.h"

class Genes
{
public:

	double getVelX();
	double getVelY();
	int getTime();

private:
	double mVelX, mVelY;
	int time;
};
