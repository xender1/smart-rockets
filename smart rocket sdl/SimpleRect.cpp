#include "SimpleRect.h"

SimpleRect::SimpleRect(SDL_Renderer* gRenderer, string path)
{
	//Initialize the offsets
	mPosX = 10;
	mPosY = 10;

	//Initialize the velocity
	mVelX = 0.0;
	mVelY = 0.0;
	mAccX = 0.0;
	mAccY = 0.0;

	mAngle = 0.0;

	unsigned char rgba[4] = { 255, 0, 0, 255 };
	//mTexture.loadFromFile(gRenderer, path);
	mTexture.createTextureRectangle(gRenderer, RECT_WIDTH, RECT_HEIGHT, rgba);

	mDot.w = RECT_WIDTH; mDot.h = RECT_HEIGHT;
	mDot.x = mPosX; mDot.y = mPosY + mDot.h;
}

SimpleRect::~SimpleRect()
{
	mTexture.free();
}

void SimpleRect::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mAccY -= RECT_ACC; break;
		case SDLK_DOWN: mAccY += RECT_ACC; break;
		case SDLK_LEFT: mAccX -= RECT_ACC; break;
		case SDLK_RIGHT: mAccX += RECT_ACC; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mAccY += RECT_ACC; break;
		case SDLK_DOWN: mAccY -= RECT_ACC; break;
		case SDLK_LEFT: mAccX += RECT_ACC; break;
		case SDLK_RIGHT: mAccX -= RECT_ACC; break;
		}
	}

}

void SimpleRect::move(vector<CollisionObject*> collisionObjects)
{
	mVelX += mAccX;
	mVelY += mAccY;

	if (mVelX > RECT_MAX_VEL) {
		mVelX = RECT_MAX_VEL;
	}
	else if (mVelX < -RECT_MAX_VEL) {
		mVelX = -RECT_MAX_VEL;
	}
	if (mVelY > RECT_MAX_VEL) {
		mVelY = RECT_MAX_VEL;
	}
	else if (mVelY < -RECT_MAX_VEL) {
		mVelY = -RECT_MAX_VEL;
	}

	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + RECT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + RECT_HEIGHT > SCREEN_HEIGHT))
	{
	//	//Move back
		mPosY -= mVelY;
	}

	mAngle = (atan2(mVelY, mVelX) * 180 / M_PI) + 90;

	//cout << mPosX << "," << mPosY << endl;
	if (checkCollision(collisionObjects)) {
		//cout << "COLLISION" << endl << endl;
		mPosX -= mVelX; mPosY -= mVelY;
	}
}

bool SimpleRect::checkCollision(vector<CollisionObject*> collisionObjects)
{
	bool collided = false;
	mCollisionBox.setCollisionBox(RECT_WIDTH, RECT_HEIGHT, mPosX + RECT_WIDTH / 2, mPosY + RECT_HEIGHT / 2, mAngle);

	//loop through collision objects and look for collisions
	for (vector<CollisionObject*>::const_iterator it = collisionObjects.begin(); it != collisionObjects.end(); ++it) {
		(*it)->setCollisionBox();
		if (mCollisionBox.calculateCollision((*it)->getCollisionBox())) {
			collided = true;
		}
	}

	return collided;
}

void SimpleRect::calculateDistance(SDL_Rect target)
{
	double dx = abs(target.x + target.w / 2) - (mPosX + mDot.w);
	double dy = abs(target.y + target.h / 2) - (mPosY + mDot.h);
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	mDist = distance;
}

void SimpleRect::render(SDL_Renderer* gRenderer)
{
	mTexture.render(gRenderer, (int)mPosX, (int)mPosY, NULL, mAngle, NULL, SDL_FLIP_NONE);
}
