#pragma once
#include "CGFEngine.h"
#include <map>

namespace CGF
{
	enum class EPhysicsType
	{
		StaticBody = 0,
		KinematicBody,
		DynamicBody
	};

	enum class EPhysicsShape
	{
		Circle = 0,
		Polygon		
	};

	struct CGF_DLL CGFImage
	{
	public:

		std::vector<std::vector<char>> ImageArray;

		CGFImage()
		{
		}
	};

	class CGF_DLL CGFActor
	{
	protected:
		CGFActor();

	public:
		virtual ~CGFActor();

		virtual void DestroyActor();

		template<typename t>
		static t* Create()
		{
			t* pActor = new t;
			return pActor;
		}

		virtual void SetVisibility(bool bVisibility);
		virtual bool IsVisible() { return bIsVisible; }

		void SetColor(COLORREF color);
		COLORREF GetColor() { return Color; }

		void SetPosition(CGFVector& Position);
		CGFVector& GetPosition();

		void SetOrigin(CGFVector& Origin);
		CGFVector& GetOrigin();

		void SetRotation(float Rotation);
		float GetRotation();

		void SetImage(CGFImage& Image) { m_Image = Image; }
		CGFImage& GetImage() { return m_Image; }

		void SetColorForKey(char key, COLORREF Color);
		COLORREF GetColorForKey(char key);

		void SetCollisionForKey(char key, bool isEnabled);
		bool GetCollisionForKey(char key);

		void CreateCollisionShape(EPhysicsShape shape, EPhysicsType type, float density = 1, float friction = 0, float restitution = 0);

		void SetParent(CGFActor* Parent);

		void AddChild(CGFActor* Child);
		bool RemoveChild(CGFActor* Child);

	protected:
		friend class CGFEngine;

		virtual void Update(float DeltaTime);

		b2Body* GetPhysicsBody();

	private:
		virtual void PhysicsUpdate();
		void Draw();

		CGFActor* m_pParent;
		CGFVector m_position;
		CGFVector m_origin;

		std::vector<CGFActor*> m_children;

		float m_rotation;
		
		bool bIsVisible;
		bool bIsPendingDestroy;

		COLORREF Color;
		CGFImage m_Image;

		std::map<char, COLORREF> Colors;
		std::map<char, bool> Collidables;

		// Box2D Implementation
		b2Shape* BodyShape;
		b2BodyDef BodyDef;
		b2Body* PhysicsBody;
	};
}