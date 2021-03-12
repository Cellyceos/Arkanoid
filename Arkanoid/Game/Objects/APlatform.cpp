//
//  Platform.cpp
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/APlatform.h"
#include "Objects/ALevel.h"

#include "Engine/Interfaces/IInputHendler.h"



#include "SDL_keycode.h"
#include "SDL_log.h"

APlatform::APlatform()
{
	SetSize({ 80.0f, 14.0f });
	GunColor = { 80, 80, 80, 255 };
}

APlatform::~APlatform()
{
	SDL_Log("~APlatform\n");
}

void APlatform::SetupPlayerInput(const TSharedPtr<IInputHandler>& InputHandler)
{
	InputHandler->BindKey(SDLK_LEFT, std::bind(&APlatform::MoveLeft, this, _1));
	InputHandler->BindKey(SDLK_RIGHT, std::bind(&APlatform::MoveRight, this, _1));
	InputHandler->BindKey(SDLK_SPACE, std::bind(&APlatform::ReleaseBall, this, _1));
}

void APlatform::MoveRight(EInputEvent KeyEvent)
{
	switch (KeyEvent)
	{
	case EInputEvent::Pressed:
		MoveSpeed = Speed;
		break;
	case EInputEvent::Released:
		MoveSpeed = 0;
		break;
	default:
		break;
	}
}

void APlatform::MoveLeft(EInputEvent KeyEvent)
{
	switch (KeyEvent)
	{
	case EInputEvent::Pressed:
		MoveSpeed = -Speed;
		break;
	case EInputEvent::Released:
		MoveSpeed = 0;
		break;
	default:
		break;
	}
}

void APlatform::ReleaseBall(EInputEvent KeyEvent)
{
	if (KeyEvent == EInputEvent::Pressed)
	{
		if (!Child.expired())
		{
			Child.lock()->Detach();
		}
	}
}

void APlatform::Update(float DeltaTime)
{
	if (MoveSpeed != 0.0f)
	{
		const float MoveDelta = MoveSpeed * DeltaTime;

		if (!Child.expired())
		{
			const auto& LockedChild = Child.lock();
			const FPoint& ChildPos = LockedChild->GetPosition();
			LockedChild->SetPosition({ ChildPos.X + MoveDelta, ChildPos.Y });
		}

		SetPosition({ Position.X + MoveDelta, Position.Y });
	}
}

void APlatform::OnCollisionEnter(const TSharedPtr<AObject>& Col)
{
	if (std::dynamic_pointer_cast<ALevel>(Col))
	{
		if (!Child.expired())
		{
			const auto& LockedChild = Child.lock();
			FPoint ChildCenter = LockedChild->GetCenterPoint();
			ChildCenter.X = Aabb.Center.X;

			LockedChild->SetCenterPoint(ChildCenter);
		}
	}
}

void APlatform::Draw(const TSharedPtr<SDLRenderer>& Renderer) const
{
	const float HalfHeight = Aabb.Radius[1];

	Renderer->SetColor(BackGroundColor);
	Renderer->FillCircle({ Position.X + HalfHeight, Aabb.Center.Y }, HalfHeight);
	Renderer->FillCircle({ Position.X + Size.Width - HalfHeight - 1.0f, Aabb.Center.Y }, HalfHeight);
	Renderer->FillRect({ Position.X + HalfHeight, Position.Y, Size.Width - Size.Height, Size.Height + 1.0f });

	const float Offset = 2.0f;
	Renderer->SetColor(ForegroundColor);
	Renderer->FillCircle({ Position.X + HalfHeight, Aabb.Center.Y }, HalfHeight - Offset);
	Renderer->FillCircle({ Position.X + Size.Width - HalfHeight - 1.0f, Aabb.Center.Y }, HalfHeight - Offset);
	Renderer->FillRect({ Position.X + HalfHeight + Offset, Position.Y + Offset, Size.Width - Size.Height - 2.0f * Offset, Size.Height + 1.0f - 2.0f * Offset });

	if (HasGun)
	{
		const float GunPlatformWidth = Size.Width * 0.125f;
		const float GunPlatformHeight = Size.Height * 0.25f;
		const float HalfHeight = GunPlatformWidth * 0.5f;
		const float HalfWidth = GunPlatformHeight * 0.5f;

		Renderer->SetColor(GunColor);
		Renderer->FillRect({ Position.X, Position.Y - GunPlatformHeight, GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Position.X + (HalfHeight - HalfWidth), Position.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });

		Renderer->FillRect({ Position.X + Size.Width - GunPlatformWidth, Position.Y - GunPlatformHeight , GunPlatformWidth, GunPlatformHeight });
		Renderer->FillRect({ Position.X + Size.Width - (HalfHeight + HalfWidth), Position.Y - GunPlatformWidth , GunPlatformHeight, GunPlatformWidth });
	}
}
