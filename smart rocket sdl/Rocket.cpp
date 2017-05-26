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

	mStartTime = SDL_GetTicks();
	mCurrTime = mStartTime;

	mDnaCount = 0;

	mAlive = true;
	mHitTarget = false;
	mFitness = 0.0;

	for (int i = 0; i < ROCKET_DNA_LENGTH; i++) {
		Gene newGene;
		newGene.randomize();
		mDna.push_back(newGene);
	}
	mGene.randomize();

}

Rocket::Rocket(SDL_Renderer * gRenderer, string path, vector<Gene> genes)
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

	mStartTime = SDL_GetTicks();
	mCurrTime = mStartTime;

	mDnaCount = 0;

	mAlive = true;
	mHitTarget = false;
	mFitness = 0.0;

	mDna.clear();
	//for (vector<Gene>::const_iterator it = genes.begin(); it != genes.end(); ++it)
	for (int i=0; i<genes.size(); i++)
	{
		//Gene newGene = genes[i];
		//mDna.push_back(*it);
		mDna.push_back(genes[i]);
	}

	//for (int i = 0; i < genes.size(); i++) {
	//	Gene newGene;
	//	newGene.randomize();
	//	mDna.push_back(newGene);
	//}
}

Rocket::Rocket(vector<Gene> genes)
{
	for (int i = 0; i<genes.size(); i++)
	{
		mDna.push_back(genes[i]);
	}
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
	mDna.clear();
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

void Rocket::setVelocityFromDna()
{
	mCurrTime = (SDL_GetTicks() - mStartTime);
	if (mDnaCount < ROCKET_DNA_LENGTH) {
		if (mCurrTime < mDna.at(mDnaCount).getTime()) {
			mVelX = mDna.at(mDnaCount).getVelX();
			mVelY = mDna.at(mDnaCount).getVelY();
		}
		else {
			mStartTime = SDL_GetTicks();
			mCurrTime = mStartTime;
			mDnaCount++;
		}
	}
	else {
		mVelX = 0;
		mVelY = 0;
		mAlive = false;
	}
	/*int i = 0;
	for (it = mDna.begin(); it < mDna.end(); it++, i++) {
		if (i == mDnaCount) {
			cout << mStartTime << " " << mCurrTime << " " << it->getTime() << " ";
			if (mCurrTime < it->getTime()) {
				//mDna.at(i).randomize();
				mVelX = it->getVelX();
				mVelY = it->getVelY();
			}
			else {
				mStartTime = SDL_GetTicks();
				mCurrTime = mStartTime;
				mDnaCount++;
			}
			break;
		}
	} */

}

void Rocket::move()
{
	//mVelX += mAccX;
	//mVelY += mAccY;
	if (mAlive && !mHitTarget) {
		setVelocityFromDna();
		//cout << mDnaCount << " " << mVelX << " " << mVelY << endl;

		//mVelX = mGene.getVelX();
		//mVelY = mGene.getVelY();

		//cout << mGene.getVelX() << " " << mGene.getVelY() << " " << mGene.getTime() << endl;

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

		if (mPosX < 0 || mPosY < 0 || mPosX + mTexture.getWidth() > SCREEN_WIDTH || mPosY + mTexture.getHeight() > SCREEN_HEIGHT) {
			mAlive = false;
		}

		//move angle
		double result = (atan2(mVelY, mVelX) * 180 / M_PI) + 90;

		if (mAngle < result) {
			mAngle += ROCKET_ANGLE_VEL;
		}
		else if (mAngle > result) {
			mAngle -= ROCKET_ANGLE_VEL;
		}
		mAngle = result;


	}
	//cout << mPosX << "," << mPosY << " " << result << " " << mAngle << endl;
}

void Rocket::checkCollision(SDL_Rect target)
{
	mMe.x = mPosX; mMe.y = mPosY;
	mMe.w = mTexture.getWidth(); mMe.h = mTexture.getHeight();
	if (calculateCollision(target, mMe)) {
		mHitTarget = true;
	}
}

bool Rocket::calculateCollision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Rocket::recreate()
{
	mDna.clear();

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

	mStartTime = SDL_GetTicks();
	mCurrTime = mStartTime;

	mDnaCount = 0;

	mAlive = true;
	mHitTarget = false;
	mFitness = 0.0;

	for (int i = 0; i < ROCKET_DNA_LENGTH; i++) {
		Gene newGene;
		newGene.randomize();
		mDna.push_back(newGene);
	}
	mGene.randomize();
}

void Rocket::render(SDL_Renderer * gRenderer)
{
	mTexture.render(gRenderer, (int)mPosX, (int)mPosY, NULL, mAngle, NULL, SDL_FLIP_NONE);
}

bool Rocket::isComplete()
{
	return (!mAlive || mHitTarget);
}

double Rocket::calculateFitness(SDL_Rect target)
{
	double score = 0.0;

	double dx = abs(target.x + target.w / 2) - (mPosX + mTexture.getWidth());
	double dy = abs(target.y + target.h / 2) - (mPosY + mTexture.getHeight());
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	score = 100*(1 / distance);
	if (distance <= 100) { score = 1.0; }

	//subtract points if crashed into wall
	if (!mAlive) score -= 0.3;
	if (mHitTarget) score = 2.0;
	
	//something with calculating total time it took to hit target or genes used


	if (score <= 0.0) { score = 0.1; }
	mFitness = score; //bad

	cout << distance << " " << mFitness << endl;

	return mFitness;
}

vector<Gene> Rocket::getDna()
{
	return mDna;
}

int Rocket::getDnaCount()
{
	return mDnaCount;
}

double Rocket::getFitnessScore()
{
	return mFitness;
}

