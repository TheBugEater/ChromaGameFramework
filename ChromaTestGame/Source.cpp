#include "CGFEngine.h"
#include "CGFGame.h"
#include "CGFActor.h"
#include "Ball.h"
#include "BGActor.h"

using namespace CGF;

/************************************************************************/
/*  The Game Logic Class - Example : Spawn Actors and Game Logic		*/
/************************************************************************/
class Game : public CGFGame
{
public:

	// Will be Called only once when the game starts
	virtual void Start()
	{
		// Spawns the BG Actor and Ball in the Level
		CGFEngine::Spawn<BGActor>();
		CGFEngine::Spawn<Ball>();
	}

	// Update will be called every tick
	virtual void Update(float delta)
	{
	}
};

int main()
{
	CGFEngine* Engine = CGFEngine::Instance();
	Engine->CreatePhysicsWorld(CGFVector(0, 1));

	Game game;
	if (Engine)
	{
		Engine->SetGameClass(&game);
		Engine->SetClearColor(CGFColors::Black);
		Engine->Run();
	}
	CGFEngine::DestroyInstance();
}