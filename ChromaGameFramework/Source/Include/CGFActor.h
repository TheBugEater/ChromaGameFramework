#pragma once
#include "CGFEngine.h"
#include <map>

namespace CGF
{
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
	public:
		CGFActor();
		virtual ~CGFActor();

		virtual void DestroyActor();

		virtual void SetVisibility(bool bVisibility);
		virtual bool IsVisible() { return bIsVisible; }

		void SetColor(COLORREF color);
		COLORREF GetColor() { return Color; }

		void SetPosition(CGFVector& Position) { m_position = Position; }
		CGFVector& GetPosition() { return m_position; }

		void SetOrigin(CGFVector& Origin) { m_origin = Origin; }
		CGFVector& GetOrigin() { return m_origin; }

		void SetRotation(float Rotation) { m_rotation = Rotation; }
		float GetRotation() { return m_rotation; }

		void SetImage(CGFImage& Image) { m_Image = Image; }
		CGFImage& GetImage() { return m_Image; }

		void AddColorForKey(char key, COLORREF Color);
		COLORREF GetColorForKey(char key);

		void SetParent(CGFActor* Parent);

		void AddChild(CGFActor* Child);
		bool RemoveChild(CGFActor* Child);

	protected:
		friend class CGFEngine;

		virtual void Update(float DeltaTime);

	private:
		void Draw();

		CGFActor* m_pParent;
		CGFVector m_position;
		CGFVector m_origin;

		std::vector<CGFActor*> m_children;

		float m_rotation;
		
		bool bIsVisible;

		COLORREF Color;
		CGFImage m_Image;

		std::map<char, COLORREF> Colors;
	};
}