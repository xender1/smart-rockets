#pragma once
#include "Rocket.h"

class Population {
public:
	Population();
	~Population();
private:
	//will have vector of rockets but right now we start with one.
	vector<Rocket> mPop;
};
