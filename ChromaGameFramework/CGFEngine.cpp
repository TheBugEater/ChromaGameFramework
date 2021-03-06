#include "CGFEngine.h"
#include "CGFActor.h"
#include "CGFGame.h"

#include <time.h>
#include <iostream>

namespace CGF
{
	void CGFContactListener::BeginContact(b2Contact* contact)
	{
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();

		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		auto ActorA = static_cast <CGFActor*>(bodyUserDataA);
		auto ActorB = static_cast <CGFActor*>(bodyUserDataB);

		if (ActorA && ActorB)
		{
			ActorA->OnCollisionEnter(ActorB);
			ActorB->OnCollisionEnter(ActorA);
		}
	}

	void CGFContactListener::EndContact(b2Contact* contact)
	{
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();

		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		auto ActorA = static_cast <CGFActor*>(bodyUserDataA);
		auto ActorB = static_cast <CGFActor*>(bodyUserDataB);

		if (ActorA && ActorB)
		{
			ActorA->OnCollisionExit(ActorB);
			ActorB->OnCollisionExit(ActorA);
		}

	}
		

	CGFEngine* CGFEngine::_pInstance = nullptr;

	CGFEngine::CGFEngine()
		: m_bExit(false)
		, PhysicsWorld(nullptr)
	{
		m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);

		Init = (INIT)GetProcAddress(m_ChromaSDKModule, "Init");
		Init();

		CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect");
		SetEffect = (SETEFFECT)GetProcAddress(m_ChromaSDKModule, "SetEffect");

	}


	CGFEngine::~CGFEngine()
	{
		if (PhysicsWorld)
		{
			delete PhysicsWorld;
			PhysicsWorld = nullptr;
		}
	}

	CGFEngine* CGFEngine::Instance()
	{
		if (_pInstance)
		{
			return _pInstance;
		}

		_pInstance = new CGFEngine();
		return _pInstance;
	}

	void CGFEngine::DestroyInstance()
	{
		if (_pInstance)
		{
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	void CGFEngine::CreatePhysicsWorld(CGFVector Gravity)
	{
		PhysicsWorld = new b2World(b2Vec2(Gravity.X, Gravity.Y));
		PhysicsWorld->SetContactListener(&m_contactListener);
	}

	b2World* CGFEngine::GetPhysicsWorld()
	{
		return PhysicsWorld;
	}

	void CGFEngine::SetGameClass(class CGFGame* pGame)
	{
		m_pGame = pGame;
	}

	void CGFEngine::SetClearColor(CGFColors Color)
	{
		ClearColor = Color;
	}

	void CGFEngine::Run()
	{
		clock_t LastClockTime = clock();

		if (m_pGame)
		{
			m_pGame->Start();

			float DrawTime = 0;

			while (!m_bExit)
			{
				clock_t CurrentTime = clock();
				float delta = float(CurrentTime - LastClockTime) / CLOCKS_PER_SEC;
				LastClockTime = CurrentTime;

				m_pGame->Update(delta);
				UpdateAll(delta);

				DrawTime += delta;
				if (DrawTime >= 0.1f)
				{
					DrawAll();
					DrawTime = 0;
				}

				// Clean Destroyed Actors
				Clean();
			}
		}

		// Clean All Actors
		Clean(true);

		Clear();
		Flush();
	}

	void CGFEngine::UpdateAll(float Delta)
	{
		auto actorIt = m_actorList.begin();
		for (actorIt; actorIt != m_actorList.end(); actorIt++)
		{
			CGFActor* pActor = *actorIt;
			if (pActor && !pActor->bIsPendingDestroy)
			{
				pActor->Update(Delta);
			}
		}

		if (PhysicsWorld)
		{
			float32 timeStep = Delta * 2;
			static const int32 velocityIterations = 8;
			static const int32 positionIterations = 4;

			PhysicsWorld->Step(timeStep, velocityIterations, positionIterations);

			actorIt = m_actorList.begin();
			for (actorIt; actorIt != m_actorList.end(); actorIt++)
			{
				CGFActor* pActor = *actorIt;
				if (pActor && !pActor->bIsPendingDestroy)
				{
					pActor->PhysicsUpdate();
				}
			}
		}
	}

	void CGFEngine::DrawAll()
	{
		auto LastCanvas = Canvas;
		Clear();

		auto actorIt = m_actorList.begin();
		for (actorIt; actorIt != m_actorList.end(); actorIt++)
		{
			CGFActor* pActor = *actorIt;
			if (pActor && pActor->IsVisible() && !pActor->bIsPendingDestroy)
			{
				// Draw here
				DrawActor(pActor);
			}
		}

		if (!CompareCanvases(LastCanvas, Canvas))
		{
			Flush();
		}
	}

	void CGFEngine::Clean(bool bForceAll)
	{
		auto actorIt = m_actorList.begin();
		while (!m_actorList.empty() && actorIt != m_actorList.end())
		{
			CGFActor* pActor = *actorIt;
			if (pActor && pActor->bIsPendingDestroy || bForceAll)
			{
				actorIt = m_actorList.erase(actorIt);
				
				delete pActor;
				pActor = nullptr;
			}
			else
			{
				++actorIt;
			}
		}
	}

	void CGFEngine::Exit()
	{
		m_bExit = true;
	}

	CGFSize CGFEngine::GetCanvasSize()
	{
		return CGFSize(22, 6);
	}

	void CGFEngine::AddActor(CGFActor* pActor)
	{
		m_actorList.push_back(pActor);
	}

	bool CGFEngine::RemoveActor(CGFActor* pActor)
	{
		m_actorList.erase(std::remove(m_actorList.begin(), m_actorList.end(), pActor), m_actorList.end());
		return true;
	}

	void CGFEngine::Clear()
	{
		for (UINT r = 0; r < ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c < ChromaSDK::Keyboard::MAX_COLUMN; c++)
			{
				Canvas.Color[r][c] = (COLORREF)ClearColor;
			}
		}
	}

	bool CGFEngine::CompareCanvases(ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Canvas1, ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Canvas2)
	{
		for (UINT r = 0; r < ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c < ChromaSDK::Keyboard::MAX_COLUMN; c++)
			{
				if (Canvas1.Color[r][c] != Canvas2.Color[r][c])
				{
					return false;
				}
			}
		}

		return true;
	}

	void CGFEngine::DrawActor(CGFActor* pActor)
	{
		CGFVector Position = pActor->GetPosition();
		CGFVector Origin = pActor->GetOrigin();
		float Rotation = pActor->GetRotation();

		CGFVector IntVector((int)round(Position.X), (int)round(Position.Y));

		for (unsigned int i = 0; i < pActor->m_Image.ImageArray.size(); i++)
		{
			auto Column = pActor->m_Image.ImageArray[i];
			for (unsigned int j = 0; j < Column.size(); j++)
			{
				COLORREF Color = pActor->GetColorForKey(Column[j]);
				if (Color != 0)
				{
					CGFVector Pos = IntVector - Origin;
					CGFVector NewPos = Pos;
					NewPos.X += j;
					NewPos.Y += i;
					NewPos = Rotate(NewPos, Pos + Origin, Rotation);

					int X = Clamp<int>((int)round(NewPos.X), 0, ChromaSDK::Keyboard::MAX_COLUMN - 1);
					int Y = Clamp<int>((int)round(NewPos.Y), 0, ChromaSDK::Keyboard::MAX_ROW - 1);

					Canvas.Color[Y][X] = pActor->GetColorForKey(Column[j]);
				}
			}
		}
	}

	void CGFEngine::Flush()
	{
		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Canvas, NULL);
		PrintStdOut();
	}

	void CGFEngine::PrintStdOut()
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, 0);
		system("CLS");

		for (UINT r = 0; r < ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c < ChromaSDK::Keyboard::MAX_COLUMN; c++)
			{
				if (Canvas.Color[r][c] != 0)
				{
					SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				}
				else
				{
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				}
				std::cout << "#";
			}

			std::cout << std::endl;
		}
	}
}