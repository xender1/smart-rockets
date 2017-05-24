#pragma once
#include "main.h"
#include "Gene.h"

//The rocket that will move around the screen
class Rocket
{
public:
	//The dimensions of the rocket
	static const int ROCKET_WIDTH = 24;
	static const int ROCKET_HEIGHT = 50;

	static const int ROCKET_DNA_LENGTH = 200;

	//max acceleration and velocity rates
	static constexpr double MAX_ROCKET_VEL = 3.0;
	static constexpr double MAX_ROCKET_ACC = 2.0;

	//acceleration
	static constexpr double ROCKET_ACC = 0.5;
	
	//speed of rotation
	static constexpr double ROCKET_ANGLE_VEL = 50.0;

	//Initializes the variables
	Rocket(SDL_Renderer* gRenderer, string path);

	~Rocket();

	void handleEvent(SDL_Event& e);

	void setVelocityFromDna();

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(SDL_Renderer * gRenderer);

private:
	//the texture for the rocket
	LTexture mTexture;

	Gene mGene;
	vector<Gene> mDna;
	vector<Gene>::iterator it;

	int mDnaCount;

	//The X and Y offsets of the rocket
	double mPosX, mPosY;

	//The velocity of the rocket
	double mVelX, mVelY;

	//THe accelartion of the rocket
	double mAccX, mAccY;
	double mVelA;

	//angle
	double mAngle;

	//for figuring out which dna segment to use
	Uint32 mStartTime;
	Uint32 mCurrTime;

	bool mAlive;

};
