#include "CollisionObject.h"



CollisionObject::CollisionObject(int w, int h, int x, int y, bool isTarget)
{
	mObject.w = w; mObject.h = h;
	mObject.x = x; mObject.y = y;
	mIsTarget = isTarget;

}


CollisionObject::~CollisionObject()
{
}

void CollisionObject::render(SDL_Renderer * gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &mObject);
}
