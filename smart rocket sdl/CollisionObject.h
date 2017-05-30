#pragma once
#include "main.h"
#include "LTexture.h"

class CollisionObject
{
public:
	CollisionObject(SDL_Renderer* gRenderer, int w, int h, int x, int y, unsigned char rgba[4], bool isTarget);
	~CollisionObject();

	//Shows the rectangle on the screen
	void render(SDL_Renderer* gRenderer);

	SDL_Rect getRect() { return mRect; }
	int getWidth() { return mRect.w; }
	int getHeight() { return mRect.h; }
	int getX() { return mRect.x; }
	int getY() { return mRect.y; }
	bool getIsTarget() { return mIsTarget; }
	double getAngle() { return mAngle; }

	void setAngle(double angle) { mAngle = angle; }


private:
	LTexture mTexture;
	//for collision
	SDL_Rect mRect;
	double mAngle;

	unsigned char* color[4];

	bool mIsTarget;
};

