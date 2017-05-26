#pragma once
#include "main.h"
#include "LTexture.h"
#include "Gene.h"

//The rocket that will move around the screen
class Rocket
{
public:
	//The dimensions of the rocket
	static const int ROCKET_WIDTH = 24;
	static const int ROCKET_HEIGHT = 50;

	static const int ROCKET_DNA_LENGTH = 10;

	//max acceleration and velocity rates
	static constexpr double MAX_ROCKET_VEL = 3.0;
	static constexpr double MAX_ROCKET_ACC = 2.0;

	//acceleration
	static constexpr double ROCKET_ACC = 0.5;
	
	//speed of rotation
	static constexpr double ROCKET_ANGLE_VEL = 5.0;

	//create rocket with random genes
	Rocket(SDL_Renderer* gRenderer, string path);
	//create rocket with given genes
	Rocket(SDL_Renderer* gRenderer, string path, vector<Gene> genes);
	//create rocket with genes (used in mating pool does not load textures only uses genes)
	Rocket(vector<Gene> genes);

	~Rocket();

	void handleEvent(SDL_Event& e);

	void setVelocityFromDna();

	//Moves the rocket from dna
	void move();

	void checkCollision(SDL_Rect target);
	bool calculateCollision(SDL_Rect A, SDL_Rect B);

	//reinitializes rocket values
	void recreate();

	//Shows the rocket on the screen
	void render(SDL_Renderer * gRenderer);

	bool isComplete();
	bool getHitTarget() { return mHitTarget; }
	double calculateFitness(SDL_Rect target);

	vector<Gene> getDna();
	int getDnaCount();
	double getFitnessScore();

private:
	//the texture for the rocket
	LTexture mTexture;

	Gene mGene;
	vector<Gene> mDna;
	vector<Gene>::iterator it;

	//current dna element being acted on
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

	SDL_Rect mMe;
	bool mHitTarget;

	//fitness score
	double mFitness;

};
