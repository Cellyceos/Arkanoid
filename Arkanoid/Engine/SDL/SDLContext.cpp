//
//  SDLContext.cpp
//  Context for correctly init and deinit SDL lib.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLContext.h"

#include "SDL.h"
#include "SDL_ttf.h"

SDLContext SDLContext::Context;

SDLContext::SDLContext()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL2, error: %s", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL_ttf lib. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL_ttf, error: %s", SDL_GetError());
		exit(1);
	}
}

SDLContext::~SDLContext()
{
	SDL_Log("~SDLContext\n");
	TTF_Quit();
	SDL_Quit();
}
