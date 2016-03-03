#include "Ball.h"
#include <iostream>

Ball::Ball()
	: ColorChange(0)
	, bIsJumping(false)
	, JumpVelocity(0)
{
	SetPosition(CGFVector(16, 1));

	SetImage(BallImage());

	AddColorForKey('O', (COLORREF)CGFColors::Red);
}


Ball::~Ball()
{
}

void Ball::Update(float delta)
{
	CGFVector Position = GetPosition();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Position.X -= delta * 10;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Position.X += delta * 10;
	}
	
	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (JumpVelocity == 0)
		{
			bIsJumping = true;
			JumpVelocity = 20;
		}
	}

	if (bIsJumping)
	{
		Position.Y -= delta * JumpVelocity;
		JumpVelocity -= delta * 2;
		if (JumpVelocity <= 0 || Position.Y < 0)
		{
			bIsJumping = false;
			JumpVelocity = 0;
		}
	}

	Position.Y += delta * 10;
	if (Position.Y > 5)
	{
		Position.Y = 5;
	}

	SetPosition(Position);

	//float Rotation = GetRotation();
	//Rotation += delta * 360;
	//SetRotation(Rotation);

	//ColorChange += delta;
	//SetColor(ColorBlend((COLORREF)CGFColors::Red, (COLORREF)CGFColors::Blue, ColorChange));


}