#pragma once
#include "main.h"
#include "LTexture.h"

//The dot that will move around on the screen
class SimpleRect
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 10;
	static const int DOT_HEIGHT = 50;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 5;

	static constexpr double DOT_ACC = 0.1;
	static constexpr double MAX_ACC = 1;
	static constexpr double MAX_VEL = 5;

	//Initializes the variables
	SimpleRect(SDL_Renderer* gRenderer, string path);
	~SimpleRect();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	void calculateDistance(SDL_Rect target);

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

	double getDistance() { return mDist; }

private:
	//the rectangle for the dot
	SDL_Rect mDot;

	LTexture mTexture;

	//The X and Y offsets of the dot
	double mPosX, mPosY;

	//The velocity of the dot
	double mVelX, mVelY;
	double mAccX, mAccY;
	double mAngle;

	double mDist;
};