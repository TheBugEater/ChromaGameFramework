#include "Ball.h"
#include <iostream>

Ball::Ball()
	: ColorChange(0)
	, bIsJumping(false)
	, JumpVelocity(0)
{
	SetPosition(CGFVector(16, 0));

	SetImage(BallImage());

	SetColorForKey('O', (COLORREF)CGFColors::Red);
	SetCollisionForKey('O', true);

	CreateCollisionShape(EPhysicsShape::Circle, EPhysicsType::DynamicBody, 1, 0.1f, 0.5f);
}


Ball::~Ball()
{
}

void Ball::Update(float delta)
{
	CGFVector Position = GetPosition();

	float X = 0, Y = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		X = -1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		X = 1;
	}
	
	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (JumpVelocity == 0)
		{
			bIsJumping = true;
			JumpVelocity = 20;
		}

		Y = -1;
	}

	if (X || Y)
	{
		GetPhysicsBody()->ApplyForceToCenter(b2Vec2(X, Y), true);
	}

	//float Rotation = GetRotation();
	//Rotation += delta * 360;
	//SetRotation(Rotation);

	/*ColorChange += delta;
	SetColor(ColorBlend((COLORREF)CGFColors::Red, (COLORREF)CGFColors::Blue, ColorChange));*/

}