//
//  SDLInputManager.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLInputManager.h"

#include "SDL.h"

SDLInputManager::SDLInputManager()
{
}

void SDLInputManager::KeyboardEvent(const FKeyboardEvent& Event)
{
	SDL_Log("Keyboard event: Key = %d, IsRepeat = %d, State = %s", Event.Key, Event.IsRepeat, (Event.State == SDL_PRESSED ? "PRESSED" : "RELEASED"));
}

void SDLInputManager::MouseButtonEvent(const FMouseButtonEvent& Event)
{
	SDL_Log("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.Button, Event.Clicks, (Event.State == SDL_PRESSED ? "PRESSED" : "RELEASED"));
}

void SDLInputManager::MouseMotionEvent(const FMouseMotionEvent& Event)
{
	SDL_Log("Mouse Motion event: X = %d, Y = %d, State = %d", Event.X, Event.Y, Event.State);
}
