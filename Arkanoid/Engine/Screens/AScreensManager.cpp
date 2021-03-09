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


AScreensManager::AScreensManager(const TSharedPtr<IScreensCreator>& InScreensCreator) : ScreensCreator(InScreensCreator)
{
	ActiveScreens.reserve(ScreensCreator->GetScreensCount());
}

AScreensManager::~AScreensManager()
{
	SDL_Log("~AScreensManager\n");
}

void AScreensManager::Update(float DeltaTime)
{
	if (RequestScreenId != IScreensCreator::InvalidRequestId)
	{
		TransitState();
	}

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

void AScreensManager::TransitState()
{
	auto EndIter = ActiveScreens.begin();
	for (; EndIter != ActiveScreens.end(); ++EndIter)
	{
		if (EndIter == ActiveScreens.end() || ((*EndIter)->GetId() == RequestScreenId))
		{
			break;
		}
	}

	if (EndIter == ActiveScreens.end())
	{
		ActiveScreens.insert(ActiveScreens.begin(), (*ScreensCreator)(weak_from_this(), RequestScreenId));
	}
	else
	{
		ActiveScreens.erase(ActiveScreens.begin(), EndIter);
	}

	RequestScreenId = IScreensCreator::InvalidRequestId;
}

void AScreensManager::RequestToQuit()
{
	SDL_Event exitEvent = { SDL_QUIT };
	SDL_PushEvent(&exitEvent);
}

/// Begin IMessageHandler
void AScreensManager::OnKeyDown(const SDL_KeyboardEvent& Event)
{
	SDL_Log("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.keysym.sym), Event.repeat > 0, "PRESSED");
	for (const auto& Screen : ActiveScreens)
	{
		if (Screen->HasBindings())
		{
			if (const auto& KeyDelegate = Screen->GetDelegateBoundToKey(Event.keysym.sym))
			{
				KeyDelegate(static_cast<EInputEvent>(Event.state));
			}
		}

		if (!Screen->ShouldHandleInputsPrevStates())
			break;
	}
}

void AScreensManager::OnKeyUp(const SDL_KeyboardEvent& Event)
{
	SDL_Log("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.keysym.sym), Event.repeat > 0, "RELEASED");
	for (const auto& Screen : ActiveScreens)
	{
		if (Screen->HasBindings())
		{
			if (const auto& KeyDelegate = Screen->GetDelegateBoundToKey(Event.keysym.sym))
			{
				KeyDelegate(static_cast<EInputEvent>(Event.state));
			}
		}

		if (!Screen->ShouldHandleInputsPrevStates())
			break;
	}
}

void AScreensManager::OnMouseButtonDown(const SDL_MouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button, Event.clicks, "PRESSED");
}

void AScreensManager::OnMouseButtonUp(const SDL_MouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button, Event.clicks, "RELEASED");
}

void AScreensManager::OnMouseMotion(const SDL_MouseMotionEvent& Event)
{
	SDL_Log("Mouse Motion event: X = %d, Y = %d, State = %d", Event.x, Event.y, Event.state);
}

void AScreensManager::OnWindowsFocusGained()
{
	if (ActiveScreens.size() > 0)
	{
		if (auto& ActiveScreen = ActiveScreens.front())
		{
			ActiveScreen->OnWindowsGainFocus();
		}
	}

	SDL_Log("Windows Focus Gained");
}

void AScreensManager::OnWindowsFocusLost()
{
	if (ActiveScreens.size() > 0)
	{
		if (auto& ActiveScreen = ActiveScreens.front())
		{
			ActiveScreen->OnWindowsLostFocus();
		}
	}

	SDL_Log("Windows Focus Lost");
}
/// End IMessageHandler
