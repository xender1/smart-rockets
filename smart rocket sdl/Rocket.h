#pragma once
#include "main.h"
#include "LTexture.h"
#include "Gene.h"
#include "CollisionObject.h"

//The rocket that will move around the screen
class Rocket
{
public:
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
	void move(vector<CollisionObject*> collisionObjects);

	bool checkCollision(vector<CollisionObject*> collisionObjects);

	//reinitializes rocket values and sets genes
	void recreate(vector<Gene> genes);

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

	//hit detection box
	CollisionBox mCollisionBox;
	bool mHitTarget;

	//fitness score
	double mFitness;

};
