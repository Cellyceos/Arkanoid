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

#include "SDL.h"

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
	SDL_Log("~SDLWindow\n");
	Renderer = nullptr;

	if (NativeWindow)
	{
		SDL_DestroyWindow(NativeWindow);
		NativeWindow = nullptr;
	}
}

bool SDLWindow::CreateWindow(const FStringView& Title, int32 Width, int32 Height)
{
	NativeWindow = SDL_CreateWindow(Title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_HIDDEN|SDL_WINDOW_ALLOW_HIGHDPI);

	if (!NativeWindow)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
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

bool SDLWindow::HandleEvents()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type) {
		case SDL_KEYDOWN:
			if (WindowID == Event.key.windowID && HasFocus() && MessageHandler)
			{
				MessageHandler->OnKeyDown(Event.key);
			}
			break;
		case SDL_KEYUP:
			if (WindowID == Event.key.windowID && HasFocus() && MessageHandler)
			{
				MessageHandler->OnKeyUp(Event.key);
			}
			break;
		case SDL_MOUSEMOTION:
			if (WindowID == Event.motion.windowID && HasFocus() && MessageHandler)
			{
				MessageHandler->OnMouseMotion(Event.motion);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (WindowID == Event.button.windowID && HasFocus() && MessageHandler)
			{
				MessageHandler->OnMouseButtonDown(Event.button);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (WindowID == Event.button.windowID && HasFocus() && MessageHandler)
			{
				MessageHandler->OnMouseButtonUp(Event.button);
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
