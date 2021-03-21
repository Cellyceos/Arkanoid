//
//  ABall.cpp
//  Ball object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/ABall.h"

#include "ALevel.h"
#include "APlatform.h"


ABall::ABall()
{
	SetSize({ 14.0f, 14.0f });
}

ABall::~ABall()
{
	LOG("~ABall\n");
}

void ABall::Update(float DeltaTime)
{
	if (!Parent.expired())
	{
		const FAABB& ParentAabb = Parent.lock()->GetAABB();
		SetCenterPoint({ ParentAabb.Center.X, ParentAabb.Center.Y - ParentAabb.Radius[1] - Aabb.Radius[1] - 1.0f });
	}
	else
	{
		SetPosition({ Position.X + Speed * Direction.X * DeltaTime, Position.Y + Speed * Direction.Y * DeltaTime });
	}
}

void ABall::OnCollisionEnter(const TSharedPtr<AObject>& Col)
{
	LOG("ABall::OnCollisionEnter %s\n", std::dynamic_pointer_cast<APlatform>(Col) ? "Platform" : (std::dynamic_pointer_cast<ALevel>(Col) ? "Level" : "Block"));
	
	if (!std::dynamic_pointer_cast<ALevel>(Col))
	{
		const FPoint& ColCenter = Col->GetCenterPoint();
		Direction = { (Aabb.Center.X - ColCenter.X) / Col->GetWidth(), Direction.Y > 0 ? -1.0f : 1.0f };
		const float Lenght = std::sqrt(Direction.X * Direction.X + Direction.Y * Direction.Y);

		Direction.X /= Lenght;
		Direction.Y /= Lenght;
	}
	else
	{
		const float BallRadius = Aabb.Radius[0];
		const FPoint& ColPosition = Col->GetPosition();
		if ((Aabb.Center.X - BallRadius) <= ColPosition.X || (Aabb.Center.X + BallRadius) >= (ColPosition.X + Col->GetWidth()))
		{
			Direction.X *= -1.0;
		}
		
		if ((Aabb.Center.Y - BallRadius) <= ColPosition.Y)
		{
			Direction.Y *= -1.0f;
		}
		else if ((Aabb.Center.Y + BallRadius) >= (ColPosition.Y + Col->GetHeight()))
		{
			bShouldBeDestroed = true;
		}
	}
}

void ABall::AttachTo(const TWeakPtr<AObject>& InParent)
{
	Parent = InParent;

	bShouldBeDestroed = false;
	Direction = UpDirection;
}

void ABall::Detach()
{
	Parent.reset();
}

void ABall::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	const float BallRadius = Aabb.Radius[0];

	Renderer->SetColor(BackGroundColor);
	Renderer->FillCircle( Aabb.Center, BallRadius);

	Renderer->SetColor(MiddleColor);
	Renderer->FillCircle({ Aabb.Center.X - 2.0f, Aabb.Center.Y - 2.5f }, BallRadius * 0.5f);

	Renderer->SetColor(ForegroundColor);
	Renderer->FillCircle({ Aabb.Center.X - 4.0f, Aabb.Center.Y - 3.0f }, BallRadius * 0.25f);
}
