#include "CGFEngine.h"
#include "CGFGame.h"
#include "CGFActor.h"
#include "Ball.h"

using namespace CGF;

struct TestActorImage : public CGFImage
{
	TestActorImage()
	{
		ImageArray = 
		{
			{ 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'O', 'O' },
			{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O', 'X', 'X', 'X' },
			{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
		};
	}
};

class TestActor : public CGFActor
{
public:

	TestActor()
	{
		SetImage(TestActorImage());

		SetPosition(CGFVector(0, 3));
		SetOrigin(CGFVector(0, 0));

		SetColorForKey('X', (COLORREF)CGFColors::Blue);

		SetCollisionForKey('X', true);

		CreateCollisionShape(PhysicsType::StaticBody);
	}

	virtual void Update(float delta)
	{
		/*float Rotation = GetRotation();
		Rotation += delta * 180;
		SetRotation(Rotation);*/
	}
};

class Game : public CGFGame
{
public:

	Ball* pActor;
	TestActor* pTest;

	Game()
	{
		pActor = new Ball();
		pTest = new TestActor();
	}

	~Game()
	{
		if (pActor)
		{
			delete pActor;
		}

		if (pTest)
		{
			delete pTest;
		}
	}

	virtual void Start()
	{
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