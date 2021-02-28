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
	SetColor(Color);
	SDL_RenderClear(NativeRenderer);
}

void SDLRenderer::SetColor(const FColor& Color)
{
	SDL_SetRenderDrawColor(NativeRenderer, Color.Red, Color.Green, Color.Blue, Color.Alpha);
}

void SDLRenderer::DrawRect(const FRect& Rect)
{	
	const SDL_Rect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderDrawRect(NativeRenderer, &NativeRect);
}

void SDLRenderer::FillRect(const FRect& Rect)
{	
	const SDL_Rect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderFillRect(NativeRenderer, &NativeRect);
}

void SDLRenderer::DrawCircle(const FPoint& Center, int32 Radius)
{
	int32 OffsetX = 0;
	int32 OffsetY = Radius;
	int32 RadiusError = Radius - 1;

	while (OffsetY >= OffsetX)
	{
		SDL_RenderDrawPoint(NativeRenderer, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPoint(NativeRenderer, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPoint(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPoint(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPoint(NativeRenderer, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPoint(NativeRenderer, Center.X + OffsetY, Center.Y - OffsetX);
		SDL_RenderDrawPoint(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPoint(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2 * OffsetX) 
		{
			RadiusError -= 2 * OffsetX + 1;
			OffsetX += 1;
		}
		else if (RadiusError < 2 * (Radius - OffsetY)) 
		{
			RadiusError += 2 * OffsetY - 1;
			OffsetY -= 1;
		}
		else 
		{
			RadiusError += 2 * (OffsetY - OffsetX - 1);
			OffsetY -= 1;
			OffsetX += 1;
		}
	}
}

void SDLRenderer::FillCircle(const FPoint& Center, int32 Radius)
{
	int32 OffsetX = 0;
	int32 OffsetY = Radius;
	int32 RadiusError = Radius - 1;

	while (OffsetY >= OffsetX) 
	{
		SDL_RenderDrawLine(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawLine(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawLine(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawLine(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX, Center.X + OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2 * OffsetX) 
		{
			RadiusError -= 2 * OffsetX + 1;
			OffsetX += 1;
		}
		else if (RadiusError < 2 * (Radius - OffsetY)) 
		{
			RadiusError += 2 * OffsetY - 1;
			OffsetY -= 1;
		}
		else 
		{
			RadiusError += 2 * (OffsetY - OffsetX - 1);
			OffsetY -= 1;
			OffsetX += 1;
		}
	}
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(NativeRenderer);
}
