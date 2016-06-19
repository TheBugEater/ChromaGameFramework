#pragma once
#include "CGFTypes.h"

#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

#include <vector>

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;

typedef RZRESULT(*INIT)(void);
typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);

namespace CGF
{

	static const float METRE_TO_PIXEL = 50;
	static const float PIXEL_TO_METRE = 0.02f;

	class CGFContactListener : public b2ContactListener
	{
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);
	};

	// Singleton Class to Handle All the Game Functionalities
	class CGF_DLL CGFEngine
	{
	private:
		CGFEngine();
		~CGFEngine();

	public:
		/** Returns an Instance of the Engine */
		static CGFEngine* Instance();

		/** Destroys the Instance of the Engine */
		static void DestroyInstance();

		template<class t>
		static t* Spawn()
		{
			t* pActor = new t;
			return pActor;
		}

		/** Sets the Default Game Class */
		void SetGameClass(class CGFGame* pGame);

		/** Sets the Clear Color */
		void SetClearColor(CGFColors Color);

		/** Creates a Physics World */
		void CreatePhysicsWorld(CGFVector Gravity);

		/** Note : Blocking Function, Starts Game Loop */
		void Run();

		/** Exits the Game */
		void Exit();

		/** Returns Canvas Size */
		CGFSize GetCanvasSize();

	private:
		friend class CGFActor;
		void AddActor(class CGFActor* pActor);
		bool RemoveActor(class CGFActor* pActor);

		void UpdateAll(float Delta);
		void DrawAll();
		void Clean(bool bForceAll = false);
		void PrintStdOut();

		static CGFEngine* _pInstance;

		class CGFGame* m_pGame;

		bool m_bExit;
		CGFColors ClearColor;

		std::vector<class CGFActor*> m_actorList;

		b2World* GetPhysicsWorld();

		// Chroma Handlers
	private:
		void Clear();
		void DrawActor(class CGFActor* Actor);
		void Flush();
		bool CompareCanvases(ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Canvas1, ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Canvas2);

		HMODULE m_ChromaSDKModule;

		CREATEKEYBOARDEFFECT CreateKeyboardEffect;
		SETEFFECT SetEffect;
		INIT Init;

		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Canvas = {};

		// Box2D

		b2World* PhysicsWorld;
		CGFContactListener m_contactListener;
	};
}