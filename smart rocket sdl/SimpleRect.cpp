#include "SimpleRect.h"

SimpleRect::SimpleRect(SDL_Renderer* gRenderer, string path)
{
	//Initialize the offsets
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT - 100;

	//Initialize the velocity
	mVelX = 0.0;
	mVelY = 0.0;
	mAccX = 0.0;
	mAccY = 0.0;

	mAngle = 0.0;

	mTexture.loadFromFile(gRenderer, path);

	mDot.w = DOT_WIDTH; mDot.h = DOT_HEIGHT;
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
		case SDLK_UP: mAccY -= DOT_ACC; break;
		case SDLK_DOWN: mAccY += DOT_ACC; break;
		case SDLK_LEFT: mAccX -= DOT_ACC; break;
		case SDLK_RIGHT: mAccX += DOT_ACC; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mAccY += DOT_ACC; break;
		case SDLK_DOWN: mAccY -= DOT_ACC; break;
		case SDLK_LEFT: mAccX += DOT_ACC; break;
		case SDLK_RIGHT: mAccX -= DOT_ACC; break;
		}
	}

}

void SimpleRect::move()
{
	mVelX += mAccX;
	mVelY += mAccY;
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
	//	//Move back
		mPosY -= mVelY;
	}

	//mDot.x = mPosX;
	//mDot.y = mPosY;

	mAngle = (atan2(mVelY, mVelX) * 180 / M_PI) + 90;
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
