//
//  SDLWindow.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLWindow.h"

#include "SDL.h"

SDLWindow::SDLWindow()
{
}

SDLWindow::~SDLWindow()
{
	Deinit();
}

bool SDLWindow::Init(const StringView Title, int32 Width, int32 Height)
{
	Window = SDL_CreateWindow(Title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_HIDDEN|SDL_WINDOW_ALLOW_HIGHDPI);
	return true;
}

void SDLWindow::Deinit()
{
	if (Window)
	{
		SDL_DestroyWindow(Window);
		Window = nullptr;
	}
}

void SDLWindow::Show()
{
	SDL_ShowWindow(Window);
}

bool SDLWindow::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}
