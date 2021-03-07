//
//  AScreensManager.cpp
//  Screen Manager based on FSM.
//
//  Created by Kirill Bravichev on 03/05/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Screens/AScreensManager.h"

#include "SDL_events.h"
#include "SDL_log.h"


AScreensManager::AScreensManager(const IScreensCreator& InScreensCreator) : ScreensCreator(InScreensCreator)
{
}

void AScreensManager::Init()
{
	ActiveScreens.insert(ActiveScreens.begin(), ScreensCreator(shared_from_this(), 0));
	ActiveScreens.insert(ActiveScreens.begin(), ScreensCreator(shared_from_this(), 1));
	ActiveScreens.insert(ActiveScreens.begin(), ScreensCreator(shared_from_this(), 2));
}

void AScreensManager::OnKeyDown(const struct SDL_KeyboardEvent& Event)
{
	SDL_Log("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.keysym.sym), Event.repeat > 0, "PRESSED");

	if (Event.keysym.sym == SDLK_ESCAPE && ActiveScreens.size() > 0)
	{
		ActiveScreens.erase(ActiveScreens.begin());
	}
}

void AScreensManager::OnKeyUp(const struct SDL_KeyboardEvent& Event)
{
	SDL_Log("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.keysym.sym), Event.repeat > 0, "RELEASED");
}

void AScreensManager::OnMouseButtonDown(const struct SDL_MouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button, Event.clicks, "PRESSED");
}

void AScreensManager::OnMouseButtonUp(const struct SDL_MouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button, Event.clicks, "RELEASED");
}

void AScreensManager::OnMouseMotion(const struct SDL_MouseMotionEvent& Event)
{
	SDL_Log("Mouse Motion event: X = %d, Y = %d, State = %d", Event.x, Event.y, Event.state);
}

void AScreensManager::OnWindowsChangeFocus()
{

}

void AScreensManager::Update(float DeltaTime)
{
	// Update All States if needed
	for (auto& Screen : ActiveScreens)
	{
		Screen->Update(DeltaTime);

		if (!Screen->ShouldUpdatePrevStates())
			break;
	}
}

void AScreensManager::Draw(const TSharedPtr<ARendererClass>& Renderer) const
{
	Renderer->Clear(BackgroundColor);

	for (auto Iter = ActiveScreens.rbegin(); Iter != ActiveScreens.rend(); ++Iter)
	{
		auto NextIter = Iter + 1;
		if (NextIter == ActiveScreens.rend() || (*NextIter)->ShouldDrawPrevScreen())
		{
			(*Iter)->Draw(Renderer);
		}
	}

	// Draw All States if needed
	Renderer->Present();
}