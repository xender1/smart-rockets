#pragma once
#include "main.h"

//The dot that will move around on the screen
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 5;
	static const int DOT_HEIGHT = 30;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 5;

	//Initializes the variables
	Dot();

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

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	double mDist;
};