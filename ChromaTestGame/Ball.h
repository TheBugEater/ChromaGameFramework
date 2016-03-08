#pragma once
#include "CGFActor.h"

using namespace CGF;

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

class Ball : public CGFActor
{
public:
	Ball();
	~Ball();

	virtual void Update(float delta);
	float ColorChange;

	virtual void OnCollisionEnter(CGFActor* OtherActor);
	virtual void OnCollisionExit(CGFActor* OtherActor);

private:

	bool bIsJumping;
	float JumpVelocity;
};
