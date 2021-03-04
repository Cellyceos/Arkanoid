//
//  SDLWindow.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLWindow.h"
#include "SDL/SDLRenderer.h"

#include "Input/InputManager.h"
#include "Input/InputEvents.h"

#include "SDL.h"


SDLWindow::SDLWindow() : AGenericWindow()
{
	BackgroundColor = { 30, 30, 30, 255 };
}

SDLWindow::~SDLWindow()
{
	Renderer = nullptr;

	if (NativeWindow)
	{
		SDL_DestroyWindow(NativeWindow);
		NativeWindow = nullptr;
	}
}

bool SDLWindow::Init(const FStringView Title, int32 Width, int32 Height)
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

bool SDLWindow::HandleEvents(const TSharedPtr<class AInputManager>& InputManager)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (WindowID == event.key.windowID && HasFocus())
			{
				InputManager->KeyboardEvent({ event.key.state, event.key.repeat > 0, event.key.keysym.sym });
			}
			break;
		case SDL_MOUSEMOTION:
			if (WindowID == event.motion.windowID && HasFocus())
			{
				InputManager->MouseMotionEvent({ event.motion.state, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel });
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			if (WindowID == event.button.windowID && HasFocus())
			{
				InputManager->MouseButtonEvent({ event.button.button, event.button.state, event.button.clicks, event.button.x, event.button.y });
			}
			break;
		case SDL_QUIT:
			return false;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				if (event.window.windowID == WindowID)
				{
					bHasFocus = true;
				}
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				if (event.window.windowID == WindowID)
				{
					bHasFocus = false;
				}
				break;
			}
			break;
		}
	}

	return true;
}

void SDLWindow::PrepareDraw()
{
	Renderer->Clear(BackgroundColor);
}

void SDLWindow::FinishDraw()
{
	Renderer->Present();
}
