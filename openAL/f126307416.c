#include "camera.h"

camera::camera()
{
	mAt[0]=0; mAt[1]=0; mAt[2]=7;
	mUp.dim(3);
	mUp[2] = 1;
	mUpAngle   = PI/10;
	mPanAngle  = PI/6;
	mPanSpeed  = .01;
	mPanAmount = PI/56;
	mDragSpeed = 500;
	mNearPlane = 100;
	mFarPlane  = 500;
	mDistance  = 80;
	mZoom = 40;
	move();
	//cout << "EYE=" << mEye << "\nAT =" << mAt << "\nUP =" << mUp << endl;
	//printf("EYE=()\nAT =()\nUP =<>");
}

double camera::EYE(int i)
{
	return mEye[i];
}

double camera::AT(int i)
{
	return mAt[i];
}

double camera::UP(int i)
{
	return mUp[i];
}

double camera::zoom()
{
	return mZoom;
}

double camera::near()
{
	return mNearPlane;
}

double camera::far()
{
	return mFarPlane;
}

void camera::move()
{	// Set near and far planes
	mNearPlane = mDistance-60;
	mFarPlane  = mDistance+50;
	if(mNearPlane <= 0)
		mNearPlane = .1;
	// Set camera position
	SpherePoint(mDistance,mUpAngle,mPanAngle,mEye);
	// Set forward and right vectors to find up vector
	Vector v(cos(mPanAngle+PI/2), sin(mPanAngle+PI/2), 0);
	Vector w(mAt[0]-mEye[0], mAt[1]-mEye[1], mAt[2]-mEye[2]);
	mUp = cross(v, w);
	mUp.unit();
}

void camera::moveUp()
{
	mUpAngle += mPanAmount;
	move();
}

void camera::moveDown()
{
	mUpAngle -= mPanAmount;
	move();
}

void camera::moveLeft()
{
	mPanAngle -= mPanAmount;
	move();
}

void camera::moveRight()
{
	mPanAngle += mPanAmount;
	move();
}

void camera::moveIn()
{
	mDistance -= 1;
	move();
}

void camera::moveOut()
{
	mDistance += 1;
	move();
}

void camera::click(int x, int y)
{
	mDX = x;
	mDY = y;
}

void camera::drag(int x, int y)
{
	mPanAngle -= (double)(x-mDX)/mDragSpeed;
	mUpAngle  -= (double)(y-mDY)/mDragSpeed;
	mDX = x;
	mDY = y;
	move();
}

void camera::pan()
{
	moveRight();
}
