#include "CGFActor.h"

namespace CGF
{

	CGFActor::CGFActor()
		: bIsVisible(true)
		, Color((COLORREF)CGFColors::White)
		, m_rotation(0)
		, m_pParent(nullptr)
	{
		CGFEngine::Instance()->AddActor(this);
	}


	CGFActor::~CGFActor()
	{
		CGFEngine::Instance()->RemoveActor(this);
	}

	void CGFActor::Update(float DeltaTime)
	{

	}

	void CGFActor::DestroyActor()
	{

	}

	void CGFActor::SetVisibility(bool bVisibility)
	{
		bIsVisible = bVisibility;
	}

	void CGFActor::SetColor(COLORREF color)
	{
		Color = color;

		auto mapIt = Colors.begin();
		for (mapIt; mapIt != Colors.end(); mapIt++)
		{
			AddColorForKey(mapIt->first, color);
		}
	}

	void CGFActor::AddColorForKey(char key, COLORREF Color)
	{
		Colors[key] = Color;
	}

	COLORREF CGFActor::GetColorForKey(char key)
	{
		return Colors[key];
	}

	void CGFActor::SetParent(CGFActor* Parent)
	{
		m_pParent = Parent;
	}

	void CGFActor::AddChild(CGFActor* Child)
	{
		m_children.push_back(Child);
	}

	bool CGFActor::RemoveChild(CGFActor* Child)
	{
		return true;
	}

	void CGFActor::Draw()
	{
		
	}
}