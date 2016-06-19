#pragma once
#include "CGFActor.h"

using namespace CGF;

/************************************************************************/
/*  Ball Image. Denotes just 1 key										*/
/************************************************************************/
struct BallImage : public CGFImage
{
	BallImage()
	{
		ImageArray =
		{
			{ 'O' }
		};
	}
};

/************************************************************************/
/*  The Ball Actor.														*/
/************************************************************************/
class Ball : public CGFActor
{
public:
	Ball();
	~Ball();

	// Update gets called every tick
	virtual void Update(float delta);

private:
	float ColorChange;
};
