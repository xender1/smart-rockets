#pragma once
#include "main.h"

class CollisionBox
{
public:
	CollisionBox();
	~CollisionBox();

	void setCollisionBox(int w, int h, double centerx, double centery, double angle);
	bool calculateCollision(CollisionBox other);

	void setAxis(double x, double x1, double y, double y1);
	double intervalDistance(double minA, double maxA, double minB, double maxB);

	double getULx() { return mULx; }
	double getULy() { return mULy; }

	double getURx() { return mURx; }
	double getURy() { return mURy; }

	double getBRx() { return mBRx; }
	double getBRy() { return mBRy; }

	double getBLx() { return mBLx; }
	double getBLy() { return mBLy; }

	double getAxisX() { return mAxisX; }
	double getAxisY() { return mAxisY; }

private:
	double mAxisX;
	double mAxisY;

	//vector<double, double> points;

	double mULx;
	double mULy;

	double mURx;
	double mURy;

	double mBLx;
	double mBLy;

	double mBRx;
	double mBRy;

};

