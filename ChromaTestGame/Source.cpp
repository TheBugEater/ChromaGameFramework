#include "CGFEngine.h"
#include "CGFGame.h"
#include "CGFActor.h"
#include "Ball.h"
#include "vld.h"

using namespace CGF;

struct BGImage : public CGFImage
{
	BGImage()
	{
		ImageArray =
		{
			{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
			{ 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X' },
			{ 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X' },
			{ 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X' },
			{ 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X' },
			{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
		};
	}
};

class BGActor : public CGFActor
{
public:

	BGActor()
	{
		SetImage(BGImage());

		SetPosition(CGFVector(0, 0));
		SetOrigin(CGFVector(0, 0));

		SetColorForKey('X', (COLORREF)CGFColors::Blue);

		SetCollisionForKey('X', true);

		CreateCollisionShape(EPhysicsShape::Polygon, EPhysicsType::StaticBody);
	}

	virtual void Update(float delta)
	{
	}
};

class Game : public CGFGame
{
public:

	virtual void Start()
	{
		CGFEngine::Create<BGActor>();
		CGFEngine::Create<Ball>();
	}

	virtual void Update(float delta)
	{
	}
};

int main()
{
	CGFEngine* Engine = CGFEngine::Instance();
	Engine->CreatePhysicsWorld(CGFVector(0, 1));

	Game* pGame = new Game;
	if (Engine && pGame)
	{
		Engine->SetGameClass(pGame);
		Engine->SetClearColor(CGFColors::Black);
		Engine->Run();
		delete pGame;
	}
	CGFEngine::DestroyInstance();
}