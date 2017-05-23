#include "Rocket.h"

Rocket::Rocket(SDL_Renderer* gRenderer, string path)
{
	//Initialize the offsets
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;

	//Initialize the velocity
	mVelX = 0.0;
	mVelY = 0.0;
	mVelA = 0.0;
	mAngle = 0.0;
	mAccX = 0;
	mAccY = 0;
	mTexture.loadFromFile(gRenderer, path);
}

Rocket::~Rocket()
{
	//Initialize the offsets
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT - 100;

	//Initialize the velocity
	mVelX = 0.0;
	mVelY = 0.0;
	mVelA = 0.0;
	mAngle = 0.0;
	mAccX = 0;
	mAccY = 0;
	mTexture.free();
}

void Rocket::handleEvent(SDL_Event & e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
	switch (e.key.keysym.sym)
		{
		case SDLK_UP: mAccY -= ROCKET_ACC; break;
		case SDLK_DOWN: mAccY += ROCKET_ACC; break;
		case SDLK_LEFT: mAccX -= ROCKET_ACC; break;
		case SDLK_RIGHT: mAccX += ROCKET_ACC; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mAccY += ROCKET_ACC; break;
		case SDLK_DOWN: mAccY -= ROCKET_ACC; break;
		case SDLK_LEFT: mAccX += ROCKET_ACC; break;
		case SDLK_RIGHT: mAccX -= ROCKET_ACC; break;
		}
	}
}

void Rocket::move()
{
	mVelX += mAccX;
	mVelY += mAccY;
	if (mVelY > MAX_ROCKET_VEL) {
		mVelY = MAX_ROCKET_VEL;
	}
	if (mVelY < -MAX_ROCKET_VEL) {
		mVelY = -MAX_ROCKET_VEL;
	}
	if (mVelX > MAX_ROCKET_VEL) {
		mVelX = MAX_ROCKET_VEL;
	}
	if (mVelX < -MAX_ROCKET_VEL) {
		mVelX = -MAX_ROCKET_VEL;
	}

	mPosX += mVelX;
	mPosY += mVelY;

	//move angle
	double result = (atan2(mVelY, mVelX) * 180 / M_PI) + 90;

	if (mAngle < result) {
		mAngle += ROCKET_ANGLE_VEL;
	}
	else if (mAngle > result) {
		mAngle -= ROCKET_ANGLE_VEL;
	}
	mAngle = result;

	//cout << mPosX << "," << mPosY << " " << result << " " << mAngle << endl;
}

void Rocket::render(SDL_Renderer * gRenderer)
{
	mTexture.render(gRenderer, (int)mPosX, (int)mPosY, NULL, mAngle, NULL, SDL_FLIP_NONE);
}

