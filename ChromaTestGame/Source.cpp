#include "CGFEngine.h"
#include "CGFGame.h"
#include "CGFActor.h"

using namespace CGF;

struct TestActorImage : public CGFImage
{
	TestActorImage()
	{
		ImageArray = 
		{
			{ 'G', 'X', 'B'}
		};
	}
};

class TestActor : public CGFActor
{
public:

	TestActor()
	{
		SetImage(TestActorImage());

		SetPosition(CGFVector(19, 3));
		SetOrigin(CGFVector(1, 0));

		AddColorForKey('G', (COLORREF)CGFColors::Green);
		AddColorForKey('X', (COLORREF)CGFColors::Red);
		AddColorForKey('B', (COLORREF)CGFColors::Blue);
	}

	virtual void Update(float delta)
	{
		float Rotation = GetRotation();
		Rotation += delta * 180;
		SetRotation(Rotation);
	}
};

class Game : public CGFGame
{
public:

	TestActor* pActor;

	Game()
	{
		pActor = new TestActor();
	}

	~Game()
	{
		if (pActor)
		{
			delete pActor;
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