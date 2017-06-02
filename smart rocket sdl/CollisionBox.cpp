#include "CollisionBox.h"



CollisionBox::CollisionBox()
{
	//setCollisionBox();
}


CollisionBox::~CollisionBox()
{
}

void CollisionBox::setCollisionBox(int w, int h, double centerx, double centery, double angle)
{
	//upper left
	double tempx = -w / 2;
	double tempy = -h / 2;
	double rotatedX = tempx*cos(angle*(M_PI / 180)) - tempy*sin(angle*(M_PI / 180));
	double rotatedY = tempx*sin(angle*(M_PI / 180)) + tempy*cos(angle*(M_PI / 180));
	mULx = centerx + rotatedX;
	mULy = centery + rotatedY;

	//upper right
	tempx = w / 2;
	tempy = -h / 2;
	rotatedX = tempx*cos(angle*(M_PI / 180)) - tempy*sin(angle*(M_PI / 180));
	rotatedY = tempx*sin(angle*(M_PI / 180)) + tempy*cos(angle*(M_PI / 180));
	mURx = centerx + rotatedX;
	mURy = centery + rotatedY;

	//bottom right
	tempx = w / 2;
	tempy = h / 2;
	rotatedX = tempx*cos(angle*(M_PI / 180)) - tempy*sin(angle*(M_PI / 180));
	rotatedY = tempx*sin(angle*(M_PI / 180)) + tempy*cos(angle*(M_PI / 180));
	mBRx = centerx + rotatedX;
	mBRy = centery + rotatedY;

	//bottom left
	tempx = -w / 2;
	tempy = h / 2;
	rotatedX = tempx*cos(angle*(M_PI / 180)) - tempy*sin(angle*(M_PI / 180));
	rotatedY = tempx*sin(angle*(M_PI / 180)) + tempy*cos(angle*(M_PI / 180));
	mBLx = centerx + rotatedX;
	mBLy = centery + rotatedY;
}

bool CollisionBox::calculateCollision(CollisionBox other)
{
	double scalarDotProduct = 0.0;

	//seperating axis theorem
	//4 times for each perpindicular axis (rectangles)
	for (int i = 0; i < 4; i++) {
		double minA = 1000000.00; double minB = 1000000.00;
		double maxA = 0.0; double maxB = 0.0;
		if (i == 0) { 	//axis 1 a top
			setAxis(mURx, mULx, mURy, mULy);
		}
		else if (i == 1) { //axis 2 a side
			setAxis(mURx, mBRx, mURy, mBRy);
		}
		else if (i == 2) { //axis 3 b top
			setAxis(other.getURx(), other.getULx(), other.getURy(), other.getULy());
		}
		else if (i == 3) { //axis 4 b side
			setAxis(other.getURx(), other.getBRx(), other.getURy(), other.getBRy());
		}

		scalarDotProduct = mAxisX * mURx + mAxisY * mURy;
		if (minA > scalarDotProduct) { minA = scalarDotProduct; }
		if (maxA < scalarDotProduct) { maxA = scalarDotProduct; }
		scalarDotProduct = mAxisX * mULx + mAxisY * mULy;
		if (minA > scalarDotProduct) { minA = scalarDotProduct; }
		if (maxA < scalarDotProduct) { maxA = scalarDotProduct; }
		scalarDotProduct = mAxisX * mBRx + mAxisY * mBRy; 
		if (minA > scalarDotProduct) { minA = scalarDotProduct; }
		if (maxA < scalarDotProduct) { maxA = scalarDotProduct; }
		scalarDotProduct = mAxisX * mBLx + mAxisY * mBLy;
		if (minA > scalarDotProduct) { minA = scalarDotProduct; }
		if (maxA < scalarDotProduct) { maxA = scalarDotProduct; }

		scalarDotProduct = mAxisX * other.getURx() + mAxisY * other.getURy();
		if (minB > scalarDotProduct) { minB = scalarDotProduct; }
		if (maxB < scalarDotProduct) { maxB = scalarDotProduct; }
		scalarDotProduct = mAxisX * other.getULx() + mAxisY * other.getULy();
		if (minB > scalarDotProduct) { minB = scalarDotProduct; }
		if (maxB < scalarDotProduct) { maxB = scalarDotProduct; }
		scalarDotProduct = mAxisX * other.getBRx() + mAxisY * other.getBRy();
		if (minB > scalarDotProduct) { minB = scalarDotProduct; }
		if (maxB < scalarDotProduct) { maxB = scalarDotProduct; }
		scalarDotProduct = mAxisX * other.getBLx() + mAxisY * other.getBLy();
		if (minB > scalarDotProduct) { minB = scalarDotProduct; }
		if (maxB < scalarDotProduct) { maxB = scalarDotProduct; }

		//if gap on any axis between rectangles then no collision possible
		if (intervalDistance(minA, maxA, minB, maxB) > 0)
		{
			return false;
		}
	}
		

	return true;
}

void CollisionBox::setAxis(double x, double x1, double y, double y1)
{
	mAxisX = y1 - y;
	mAxisY = x - x1;
}

double CollisionBox::intervalDistance(double minA, double maxA, double minB, double maxB)
{
	if (minA < minB) {
		return minB - maxA;
	}
	else {
		return minA - maxB;
	}
}

