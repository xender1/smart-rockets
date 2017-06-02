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
	mTexture.render(gRenderer, mRect.x, mRect.y, NULL, mAngle, NULL, SDL_FLIP_NONE);
}

void CollisionObject::setCollisionBox()
{
	mCollisionBox.setCollisionBox(getWidth(), getHeight(), getX() + getWidth()/2, getY() + getHeight() / 2, mAngle);
}
