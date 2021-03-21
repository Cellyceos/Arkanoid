//
//  SDLContext.cpp
//  Context for correctly init and deinit SDL lib.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLContext.h"

#ifdef USE_SDL
#include "SDL.h"

#ifdef USE_SDL_TTF
#include "SDL_ttf.h"
#endif // USE_SDL_TTF

#ifdef USE_SDL_IMG
#include "SDL_image.h"
#endif // USE_SDL_IMG

#include "Engine/Logging/Macros.h"


SDLContext SDLContext::Context;

SDLContext::SDLContext()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info.", NULL);
		LOG_CRITICAL("Unable to init SDL2, error: %s", SDL_GetError());
		exit(1);
	}

#ifdef USE_SDL_TTF
	if (TTF_Init() != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL_ttf lib. See the log for more info.", NULL);
		LOG_CRITICAL("Unable to init SDL_ttf, error: %s", SDL_GetError());
		exit(1);
	}
#endif // USE_SDL_TTF

#ifdef USE_SDL_IMG
	if (IMG_Init(IMG_INIT_TIF | IMG_INIT_PNG | IMG_INIT_WEBP) == 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL_image lib. See the log for more info.", NULL);
		LOG_CRITICAL("Unable to init SDL_image, error: %s", SDL_GetError());
		exit(1);
	}
#endif // USE_SDL_ING

}

SDLContext::~SDLContext()
{
#ifdef USE_SDL_IMG
	IMG_Quit();
#endif // USE_SDL_ING

#ifdef USE_SDL_TTF
	TTF_Quit();
#endif // USE_SDL_TTF

	SDL_Quit();

	LOG("~SDLContext\n");
}
#endif // USE_SDL
