#include "BGActor.h"


BGActor::BGActor()
{
	// Set BG Image as Actor's Image
	SetImage(BGImage());

	// Set BG Position and Origin
	SetPosition(CGFVector(0, 0));
	SetOrigin(CGFVector(0, 0));

	// Set Key Color and Collision
	SetColorForKey('X', (COLORREF)CGFColors::Blue);
	SetCollisionForKey('X', true);

	// Create a Polygon Shaped Object with Static Body Physics
	CreateCollisionShape(EPhysicsShape::Polygon, EPhysicsType::StaticBody);
}

void BGActor::OnCollisionEnter(CGFActor* OtherActor)
{
	// Change Color to Red when there is a collision.
	SetColorForKey('X', (COLORREF)CGFColors::Red);
}

void BGActor::OnCollisionExit(CGFActor* OtherActor)
{
	// Change Back to Blue when there is no more collision.
	SetColorForKey('X', (COLORREF)CGFColors::Blue);
}