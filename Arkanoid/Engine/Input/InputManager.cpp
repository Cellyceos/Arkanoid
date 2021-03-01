//
//  InputManager.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Input/InputManager.h"
#include "Input/InputEvents.h"

#include "SDL.h"

AInputManager::AInputManager()
{
	//AxisKeyMap.insert({ "Move", {{ FInputAxisKeyMapping("Move", SDLK_RIGHT, 1.0f), FInputAxisKeyMapping("Move", SDLK_LEFT, -1.0f) }} });
}

void AInputManager::KeyboardEvent(const FKeyboardEvent& Event)
{
	if (Event.Key == SDLK_LEFT || Event.Key == SDLK_RIGHT)
	{
		if (Event.State == SDL_PRESSED)
		{
			AxisBindings[0].AxisDelegate((Event.Key == SDLK_LEFT ? -1.0f : 1.0f));
		}
		else if (Event.State == SDL_RELEASED)
		{
			AxisBindings[0].AxisDelegate(0.0);
		}
	}
	SDL_Log("Keyboard event: Key = %d, IsRepeat = %d, State = %s", Event.Key, Event.IsRepeat, (Event.State == SDL_PRESSED ? "PRESSED" : "RELEASED"));
}

void AInputManager::MouseButtonEvent(const FMouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.Button, Event.Clicks, (Event.State == SDL_PRESSED ? "PRESSED" : "RELEASED"));
}

void AInputManager::MouseMotionEvent(const FMouseMotionEvent& Event)
{
	SDL_Log("Mouse Motion event: X = %d, Y = %d, State = %d", Event.X, Event.Y, Event.State);
}

void AInputManager::BindAxis(const FString& AxisName, TFunction<void(float)> Function)
{
	FInputAxisBinding AB(AxisName);
	AB.AxisDelegate = Function;

	AxisBindings.push_back(std::move(AB));
}

void AInputManager::BindAction(const FString& ActionName, EInputEvent KeyEvent, TFunction<void(void)> Function)
{
	FInputActionBinding AB(ActionName, KeyEvent);
	AB.ActionDelegate = Function;

	ActionBindings.push_back(std::move(AB));
}
