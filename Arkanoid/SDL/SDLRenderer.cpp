//
//  SDLRenderer.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLRenderer.h"

#include "SDL.h"

SharedPtr<SDLRenderer> SDLRenderer::Construct(SDL_Window* Window)
{
	SDL_Renderer* NativeRenderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (!NativeRenderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create renderer. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
		return nullptr;
	}

	return MakeShared<SDLRenderer>(NativeRenderer);
}

SDLRenderer::SDLRenderer(SDL_Renderer* Renderer) : NativeRenderer(Renderer) { }

SDLRenderer::~SDLRenderer()
{
	if (NativeRenderer)
	{
		SDL_DestroyRenderer(NativeRenderer);
		NativeRenderer = nullptr;
	}
}

void SDLRenderer::Clear(const FColor& Color)
{
	SDL_SetRenderDrawColor(NativeRenderer, Color.Red, Color.Green, Color.Blue, Color.Alpha);
	SDL_RenderClear(NativeRenderer);
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(NativeRenderer);
}
