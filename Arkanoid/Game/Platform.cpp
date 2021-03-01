//
//  Platform.cpp
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/Platform.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/IRenderer.h"


APlatform::APlatform()
{
	Rect = { 300.0f, 500.0f, 80.0f, 14.0f };
	Color = { 150, 150, 150, 255 };
	GunColor = { 80, 80, 80, 255 };
}

APlatform::~APlatform()
{

}

void APlatform::SetupPlayerInput(const TSharedPtr<class AInputManager>& InputManager)
{
	InputManager->BindAxis("Move", std::bind(&APlatform::Move, this, _1));
	InputManager->BindAction("Release", EInputEvent::IE_Pressed, std::bind(&APlatform::ReleaseBall, this));
}

void APlatform::SetOwner(const TWeakPtr<AObject>& NewOwner)
{
	AObject::SetOwner(NewOwner);

	if (!Owner.expired())
	{
		const FRect& OwnerRect = Owner.lock()->GetRect();
		Rect.Y = OwnerRect.Height - Rect.Height - 15.0f;
	}
}

void APlatform::Move(float Val)
{
	MoveDirection = Val;
}

void APlatform::ReleaseBall()
{

}

void APlatform::Update(float DeltaTime)
{
	if (MoveDirection != 0.0f)
	{
		Rect.X += MoveDirection;

	}

	if (!Owner.expired())
	{
		const FRect& OwnerRect = Owner.lock()->GetRect();
		const float HalfHeight = Rect.Height * 0.5f;

		if (Rect.X + Rect.Width + HalfHeight > OwnerRect.X + OwnerRect.Width)
		{
			Rect.X = OwnerRect.X + OwnerRect.Width - Rect.Width - HalfHeight;
		}
		else if (Rect.X - HalfHeight < OwnerRect.X)
		{
			Rect.X = OwnerRect.X + HalfHeight;
		}
	}
}

void APlatform::Draw(const TSharedPtr<class IRenderer>& Renderer)
{
	const float HalfHeight = Rect.Height * 0.5f;
	const float HalfWidth = Rect.Width * 0.5f;

	const FPoint& Center = GetCenterPoint();

	Renderer->SetColor(Color);
	Renderer->FillCircle({ Rect.X, Center.Y }, HalfHeight);
	Renderer->FillCircle({ Rect.X + Rect.Width, Center.Y }, HalfHeight);
	Renderer->FillRect({ Rect.X, Rect.Y, Rect.Width, Rect.Height + 1.0f });

	if (HasGun)
	{
		const float GunPlatformWidth = Rect.Width * 0.125f;
		const float GunPlatformHeight = Rect.Height * 0.25f;
		const float HalfHeight = GunPlatformWidth * 0.5f;
		const float HalfWidth = GunPlatformHeight * 0.5f;

		Renderer->SetColor(GunColor);
		Renderer->FillRect({ Rect.X, Rect.Y - GunPlatformHeight, GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Rect.X + (HalfHeight - HalfWidth), Rect.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });

		Renderer->FillRect({ Rect.X + Rect.Width - GunPlatformWidth, Rect.Y - GunPlatformHeight , GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Rect.X + Rect.Width - (HalfHeight + HalfWidth), Rect.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });
	}
}
