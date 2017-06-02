#pragma once
#include "main.h"
#include "LTexture.h"
#include "CollisionObject.h"

//The dot that will move around on the screen
class SimpleRect
{
public:
	//The dimensions of the dot
	static const int RECT_WIDTH = 20;
	static const int RECT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int RECT_VEL = 5;

	static constexpr double RECT_ACC = 1;// 0.1;
	static constexpr double RECT_MAX_ACC = 1;
	static constexpr double RECT_MAX_VEL = 5;

	//Initializes the variables
	SimpleRect(SDL_Renderer* gRenderer, string path);
	~SimpleRect();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(vector<CollisionObject*> collisionObjects);
	bool checkCollision(vector<CollisionObject*> collisionObjects);

	void calculateDistance(SDL_Rect target);

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

	double getDistance() { return mDist; }

	string getCoords() { string ret; ret = to_string((int)mPosX); ret.append(","); ret.append(to_string((int)mPosY)); return ret; }

	CollisionBox getCollisionBox() { return mCollisionBox; }

private:
	//the rectangle for the dot
	SDL_Rect mDot;

	CollisionBox mCollisionBox;

	LTexture mTexture;

	//The X and Y offsets of the dot
	double mPosX, mPosY;

	//The velocity of the dot
	double mVelX, mVelY;
	double mAccX, mAccY;
	double mAngle;

	double mDist;
};