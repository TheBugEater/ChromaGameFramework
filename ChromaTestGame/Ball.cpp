#include "Ball.h"
#include <iostream>

Ball::Ball()
	: ColorChange(0)
{
	// Set Ball's default Position
	SetPosition(CGFVector(16, 1));

	// Set Ball Image as the Actor's Image
	SetImage(BallImage());

	// Set Key Color and Collision
	SetColorForKey('O', (COLORREF)CGFColors::Green);
	SetCollisionForKey('O', true);

	// Create a Circle Shaped Object with Dynamic Physics with Density 1, Friction 0.5 and Restitution 0.8
	CreateCollisionShape(EPhysicsShape::Circle, EPhysicsType::DynamicBody, 1, .5f, 0.8f);
}


Ball::~Ball()
{
}

void Ball::Update(float delta)
{
	CGFVector Position = GetPosition();

	float X = 0, Y = 0;

	// Move Ball to the Left or Right If Corresponding Keys are pressed
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		X = -1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		X = 1;
	}

	// Move Ball upwards if Up is pressed
	if(GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Y = -1;
	}

	// Exit the Game when Escape is pressed
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		CGFEngine::Instance()->Exit();
	}


	if (X || Y)
	{
		// Applies the Force to the Object
		GetPhysicsBody()->ApplyForceToCenter(b2Vec2(X, Y), true);
	}
}