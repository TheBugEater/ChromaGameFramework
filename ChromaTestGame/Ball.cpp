#include "Ball.h"
#include <iostream>

Ball::Ball()
	: ColorChange(0)
	, bIsJumping(false)
	, JumpVelocity(0)
{
	SetPosition(CGFVector(16, 1));

	SetImage(BallImage());

	SetColorForKey('O', (COLORREF)CGFColors::Red);
	SetCollisionForKey('O', true);

	CreateCollisionShape(PhysicsType::DynamicBody);
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

		//GetPhysicsBody()->ApplyForce(b2Vec2(0, -10), GetPosition().ToB2Vec(), true);
	}

	//float Rotation = GetRotation();
	//Rotation += delta * 360;
	//SetRotation(Rotation);

	//ColorChange += delta;
	//SetColor(ColorBlend((COLORREF)CGFColors::Red, (COLORREF)CGFColors::Blue, ColorChange));


}