#include "CGFEngine.h"
#include "CGFActor.h"
#include "CGFGame.h"

#include <time.h>
#include <iostream>

namespace CGF
{
	CGFEngine* CGFEngine::_pInstance = nullptr;

	CGFEngine::CGFEngine()
		: m_bExit(false)
	{
		m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);

		Init = (INIT)GetProcAddress(m_ChromaSDKModule, "Init");
		Init();

		CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect");
		SetEffect = (SETEFFECT)GetProcAddress(m_ChromaSDKModule, "SetEffect");
	}


	CGFEngine::~CGFEngine()
	{
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
			}
		}

		Clear();
		Flush();
	}

	void CGFEngine::UpdateAll(float Delta)
	{
		auto actorIt = m_actorList.begin();
		for (actorIt; actorIt != m_actorList.end(); actorIt++)
		{
			CGFActor* pActor = *actorIt;
			if (pActor)
			{
				pActor->Update(Delta);
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
			if (pActor && pActor->IsVisible())
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
		// m_actorList.erase(pActor);
		auto position = std::find(m_actorList.begin(), m_actorList.end(), pActor);
		m_actorList.erase(position);
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
				CGFVector Pos = IntVector - Origin;
				CGFVector NewPos = Pos;
				NewPos.X += j;
				NewPos.Y += i;
				NewPos = Rotate(NewPos, Pos + Origin, Rotation);

				int X = Clamp<int>((int)round(NewPos.X), 0, 21);
				int Y = Clamp<int>((int)round(NewPos.Y), 0, 5);

				Canvas.Color[Y][X] = pActor->GetColorForKey(Column[j]);
			}
		}

		//int X = Clamp<int>((int)Position.X, 0, 21);
		//int Y = Clamp<int>((int)Position.Y, 0, 5);
		//Canvas.Color[Y][X] = pActor->GetColor();
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