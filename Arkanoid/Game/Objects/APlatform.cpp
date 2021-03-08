//
//  Platform.cpp
//  Player controlled object.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/APlatform.h"

#include "Engine/Interfaces/IInputHendler.h"

#include "SDL_keycode.h"
#include "SDL_log.h"

APlatform::APlatform()
{
	Size = { 80.0f, 14.0f };
	GunColor = { 80, 80, 80, 255 };
}

APlatform::~APlatform()
{

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
		SDL_Log("Release Ball");
	}
}

void APlatform::Update(float DeltaTime)
{
	if (MoveSpeed != 0.0f)
	{
		Position.X += MoveSpeed * DeltaTime;
	}
}

void APlatform::Draw(const TSharedPtr<SDLRenderer>& Renderer) const
{
	const float HalfHeight = Size.Height * 0.5f;
	const float HalfWidth = Size.Width * 0.5f;

	const FPoint& Center = GetCenterPoint();

	Renderer->SetColor(BackGroundColor);
	Renderer->FillCircle({ Position.X + HalfHeight, Center.Y }, HalfHeight);
	Renderer->FillCircle({ Position.X + Size.Width - HalfHeight - 1.0f, Center.Y }, HalfHeight);
	Renderer->FillRect({ Position.X + HalfHeight, Position.Y, Size.Width - Size.Height, Size.Height + 1.0f });

	const float Offset = 2.0f;
	Renderer->SetColor(ForegroundColor);
	Renderer->FillCircle({ Position.X + HalfHeight, Center.Y }, HalfHeight - Offset);
	Renderer->FillCircle({ Position.X + Size.Width - HalfHeight - 1.0f, Center.Y }, HalfHeight - Offset);
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
