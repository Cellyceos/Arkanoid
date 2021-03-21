//
//  SDLWindow.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLWindow.h"
#include "SDL/SDLRenderer.h"
#include "Interfaces/IMessageHendler.h"

#include "SDL_video.h"
#include "SDL_events.h"
#include "SDL_messagebox.h"


SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
	Renderer = nullptr;

	if (NativeWindow)
	{
		SDL_DestroyWindow(NativeWindow);
		NativeWindow = nullptr;
	}

	LOG("~SDLWindow\n");
}

bool SDLWindow::CreateWindow(const FStringView& Title, int32 Width, int32 Height)
{
	NativeWindow = SDL_CreateWindow(Title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_HIDDEN|SDL_WINDOW_ALLOW_HIGHDPI);

	if (!NativeWindow)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.", NULL);
		LOG_CRITICAL("Unable to create window, error: %s", SDL_GetError());
		return false;
	}

	WindowID = SDL_GetWindowID(NativeWindow);
	Renderer = SDLRenderer::Construct(NativeWindow);
	return Renderer != nullptr;
}

void SDLWindow::Show()
{
	SDL_ShowWindow(NativeWindow);
}

void SDLWindow::Hide()
{
	SDL_HideWindow(NativeWindow);
}

int32 SDLWindow::GetWidth() const
{
	int32 Width = 0;
	SDL_GetWindowSize(NativeWindow, &Width, nullptr);
	return Width;
}

int32 SDLWindow::GetHeight() const
{
	int32 Height = 0;
	SDL_GetWindowSize(NativeWindow, nullptr, &Height);
	return Height;
}

void SDLWindow::SendQuitMessage()
{
	SDL_Event exitEvent = { SDL_QUIT };
	SDL_PushEvent(&exitEvent);
}

bool SDLWindow::HandleEvents()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type) {
		case SDL_KEYDOWN:
			if (WindowID == Event.key.windowID && HasFocus() && MessageHandler)
			{
				LOG("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.key.keysym.sym), Event.key.repeat > 0, "PRESSED");
				MessageHandler->OnKeyDown({ EInputState::Pressed, Event.key.repeat > 0, static_cast<EInputKey>(Event.key.keysym.sym) });
			}
			break;
		case SDL_KEYUP:
			if (WindowID == Event.key.windowID && HasFocus() && MessageHandler)
			{
				LOG("Keyboard event: Key = %s, IsRepeat = %d, State = %s", SDL_GetKeyName(Event.key.keysym.sym), Event.key.repeat > 0, "RELEASED");
				MessageHandler->OnKeyUp({ EInputState::Released, Event.key.repeat > 0, static_cast<EInputKey>(Event.key.keysym.sym) });
			}
			break;
		case SDL_MOUSEMOTION:
			if (WindowID == Event.motion.windowID && HasFocus() && MessageHandler)
			{
				LOG("Mouse Motion event: X = %d, Y = %d, State = %d", Event.motion.x, Event.motion.y, Event.motion.state);
				MessageHandler->OnMouseMotion({ Event.motion.state, Event.motion.x, Event.motion.y, Event.motion.xrel, Event.motion.yrel });
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (WindowID == Event.button.windowID && HasFocus() && MessageHandler)
			{
				LOG("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button.button, Event.button.clicks, "PRESSED");
				MessageHandler->OnMouseButtonDown({ static_cast<EMouseButtonType>(Event.button.button), EInputState::Pressed, Event.button.clicks, Event.button.x, Event.button.y });
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (WindowID == Event.button.windowID && HasFocus() && MessageHandler)
			{
				LOG("Mouse Button event: Button = %d, Clicks = %d, State = %s", Event.button.button, Event.button.clicks, "RELEASED");
				MessageHandler->OnMouseButtonUp({ static_cast<EMouseButtonType>(Event.button.button), EInputState::Released, Event.button.clicks, Event.button.x, Event.button.y });
			}
			break;
		case SDL_QUIT:
			return false;
		case SDL_WINDOWEVENT:
			switch (Event.window.event) {
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				if (Event.window.windowID == WindowID)
				{
					bHasFocus = true;
					if (MessageHandler)
					{
						MessageHandler->OnWindowsFocusGained();
					}
				}
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				if (Event.window.windowID == WindowID)
				{
					bHasFocus = false;
					if (MessageHandler)
					{
						MessageHandler->OnWindowsFocusLost();
					}
				}
				break;
			}
			break;
		}
	}

	return true;
}
