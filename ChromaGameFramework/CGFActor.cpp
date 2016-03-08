#include "CGFActor.h"

namespace CGF
{
	CGFActor::CGFActor()
		: bIsVisible(true)
		, Color((COLORREF)CGFColors::White)
		, m_rotation(0)
		// , m_pParent(nullptr)
		, BodyShape(nullptr)
		, PhysicsBody(nullptr)
		, bIsPendingDestroy(false)
	{
		CGFEngine::Instance()->AddActor(this);
	}


	CGFActor::~CGFActor()
	{
		CGFEngine::Instance()->RemoveActor(this);

		if (PhysicsBody)
		{
			CGFEngine::Instance()->GetPhysicsWorld()->DestroyBody(PhysicsBody);
			PhysicsBody = nullptr;
		}
	}

	void CGFActor::Update(float DeltaTime)
	{

	}

	void CGFActor::DestroyActor()
	{
		bIsPendingDestroy = true;
	}

	void CGFActor::SetPosition(CGFVector& Position)
	{
		m_position = Position; 

		if (GetPhysicsBody())
		{
			GetPhysicsBody()->SetTransform(m_position.ToB2Vec(), m_rotation * (float)Deg2Rad);
		}
	}

	CGFVector& CGFActor::GetPosition()
	{ 
		return m_position; 
	}

	void CGFActor::SetOrigin(CGFVector& Origin)
	{ 
		m_origin = Origin; 

		if (GetPhysicsBody())
		{
			GetPhysicsBody()->SetTransform(m_position.ToB2Vec(), m_rotation * (float)Deg2Rad);
		}
	}

	CGFVector& CGFActor::GetOrigin()
	{ 
		return m_origin; 
	}

	void CGFActor::SetRotation(float Rotation)
	{
		m_rotation = Rotation;

		if (GetPhysicsBody())
		{
			GetPhysicsBody()->SetTransform(m_position.ToB2Vec(), m_rotation * (float)Deg2Rad);
		}
	}

	float CGFActor::GetRotation()
	{ 
		return m_rotation; 
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
			SetColorForKey(mapIt->first, color);
		}
	}

	void CGFActor::SetColorForKey(char key, COLORREF Color)
	{
		Colors[key] = Color;
	}

	COLORREF CGFActor::GetColorForKey(char key)
	{
		return Colors[key];
	}

	void CGFActor::SetCollisionForKey(char key, bool isEnabled)
	{
		Collidables[key] = isEnabled;
	}

	bool CGFActor::GetCollisionForKey(char key)
	{
		return Collidables[key];
	}

	b2Body* CGFActor::GetPhysicsBody()
	{
		return PhysicsBody;
	}

	void CGFActor::CreateCollisionShape(EPhysicsShape shape, EPhysicsType type, float density, float friction, float restitution)
	{
		BodyDef.type = (b2BodyType)type;
		BodyDef.position = b2Vec2(m_position.X, m_position.Y);
		BodyDef.angle = m_rotation * (float)Deg2Rad;

		b2World* const pWorld = CGFEngine::Instance()->GetPhysicsWorld();
		if (!pWorld)
			return;

		PhysicsBody = pWorld->CreateBody(&BodyDef);

		float Size = PIXEL_TO_METRE * 50;

		if (shape == EPhysicsShape::Polygon)
		{
			for (unsigned int i = 0; i < m_Image.ImageArray.size(); i++)
			{
				auto Column = m_Image.ImageArray[i];
				for (unsigned int j = 0; j < Column.size(); j++)
				{
					bool IsCollidable = GetCollisionForKey(Column[j]);
					if (IsCollidable)
					{
						b2PolygonShape boxShape;
						b2Vec2 Vertices[4];
						Vertices[0].Set(j * Size, i * Size);
						Vertices[1].Set(Size + j * Size, i * Size);
						Vertices[2].Set(Size + j * Size, Size + i * Size);
						Vertices[3].Set(j * Size, Size + i * Size);

						boxShape.Set(Vertices, 4);

						b2FixtureDef boxFixtureDef;
						boxFixtureDef.shape = &boxShape;
						boxFixtureDef.density = density;
						boxFixtureDef.friction = friction;
						boxFixtureDef.restitution = restitution;
						PhysicsBody->CreateFixture(&boxFixtureDef);
					}
				}
			}
		}
		else if (shape == EPhysicsShape::Circle)
		{
			float Width = m_Image.ImageArray[0].size() * Size;

			b2CircleShape circularShape;
			circularShape.m_radius = (float)Width/2;
			circularShape.m_p = b2Vec2((float)Width / 2, (float)Width / 2);

			b2FixtureDef circleFixtureDef;
			circleFixtureDef.shape = &circularShape;
			circleFixtureDef.density = density;
			circleFixtureDef.friction = friction;
			circleFixtureDef.restitution = restitution;

			PhysicsBody->CreateFixture(&circleFixtureDef);

		}

		PhysicsBody->SetUserData(this);
	}

	void CGFActor::PhysicsUpdate()
	{
		if (!PhysicsBody || PhysicsBody && PhysicsBody->GetType() == b2_staticBody)
			return;

		auto postion = PhysicsBody->GetPosition();
		auto rotation = PhysicsBody->GetAngle();

		m_position = CGFVector(postion.x, postion.y);
		m_rotation = rotation * (float)Rad2Deg;
	}

	void CGFActor::OnCollisionEnter(CGFActor* OtherActor)
	{

	}

	void CGFActor::OnCollisionExit(CGFActor* OtherActor)
	{

	}

	//void CGFActor::SetParent(CGFActor* Parent)
	//{
	//	m_pParent = Parent;
	//}

	//void CGFActor::AddChild(CGFActor* Child)
	//{
	//	m_children.push_back(Child);
	//}

	//bool CGFActor::RemoveChild(CGFActor* Child)
	//{
	//	return true;
	//}

	void CGFActor::Draw()
	{
		
	}
}