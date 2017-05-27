#pragma once
#include <SDL.h>

class CollisionObject
{
public:
	CollisionObject(int w, int h, int x, int y, bool isTarget);
	CollisionObject(SDL_Rect rect, bool isTarget);
	~CollisionObject();

	//Shows the rectangle on the screen
	void render(SDL_Renderer* gRenderer);

	SDL_Rect getRect() { return mObject; }
	int getWidth() { return mObject.w; }
	int getHeight() { return mObject.h; }
	int getX() { return mObject.x; }
	int getY() { return mObject.y; }
	bool getIsTarget() { return mIsTarget; }


private:
	SDL_Rect mObject;
	bool mIsTarget;
};

