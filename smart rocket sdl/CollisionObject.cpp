#include "CollisionObject.h"



CollisionObject::CollisionObject(SDL_Renderer* gRenderer, int w, int h, int x, int y, unsigned char rgba[4], bool isTarget)
{
	mRect.w = w; mRect.h = h;
	mRect.x = x; mRect.y = y;
	mIsTarget = isTarget;
	mTexture.createTextureRectangle(gRenderer, w, h, rgba);
	mAngle = 0.0;
}

CollisionObject::~CollisionObject()
{
	mTexture.free();
}

void CollisionObject::render(SDL_Renderer * gRenderer)
{
	//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(gRenderer, &mRect);
	mTexture.render(gRenderer, mRect.x, mRect.y, NULL, mAngle, NULL, SDL_FLIP_NONE);
}
