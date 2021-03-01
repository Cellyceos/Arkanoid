//
//  SDLRenderer.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLRenderer.h"

#include "SDL.h"

TSharedPtr<SDLRenderer> SDLRenderer::Construct(SDL_Window* Window)
{
	SDL_Renderer* NativeRenderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (!NativeRenderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create renderer. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
		return nullptr;
	}

	return std::make_shared<SDLRenderer>(NativeRenderer);
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
	const SDL_FRect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderDrawRectF(NativeRenderer, &NativeRect);
}

void SDLRenderer::FillRect(const FRect& Rect)
{	
	const SDL_FRect NativeRect{Rect.X, Rect.Y, Rect.Width, Rect.Height};
	SDL_RenderFillRectF(NativeRenderer, &NativeRect);
}

void SDLRenderer::DrawCircle(const FPoint& Center, float Radius)
{
	float OffsetX = 0.0f;
	float OffsetY = Radius;
	float RadiusError = Radius - 1.0f;

	while (OffsetY >= OffsetX)
	{
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X + OffsetY, Center.Y - OffsetX);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawPointF(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2.0f * OffsetX) 
		{
			RadiusError -= 2.0f * OffsetX + 1.0f;
			OffsetX += 1.0f;
		}
		else if (RadiusError < 2.0f * (Radius - OffsetY)) 
		{
			RadiusError += 2.0f * OffsetY - 1.0f;
			OffsetY -= 1.0f;
		}
		else 
		{
			RadiusError += 2.0f * (OffsetY - OffsetX - 1.0f);
			OffsetY -= 1.0f;
			OffsetX += 1.0f;
		}
	}
}

void SDLRenderer::FillCircle(const FPoint& Center, float Radius)
{
	float OffsetX = 0.0f;
	float OffsetY = Radius;
	float RadiusError = Radius - 1.0f;

	while (OffsetY >= OffsetX) 
	{
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetY, Center.Y + OffsetX, Center.X + OffsetY, Center.Y + OffsetX);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetX, Center.Y + OffsetY, Center.X + OffsetX, Center.Y + OffsetY);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetX, Center.Y - OffsetY, Center.X + OffsetX, Center.Y - OffsetY);
		SDL_RenderDrawLineF(NativeRenderer, Center.X - OffsetY, Center.Y - OffsetX, Center.X + OffsetY, Center.Y - OffsetX);

		if (RadiusError >= 2.0f * OffsetX) 
		{
			RadiusError -= 2.0f * OffsetX + 1.0f;
			OffsetX += 1.0f;
		}
		else if (RadiusError < 2.0f * (Radius - OffsetY)) 
		{
			RadiusError += 2.0f * OffsetY - 1.0f;
			OffsetY -= 1.0f;
		}
		else 
		{
			RadiusError += 2.0f * (OffsetY - OffsetX - 1.0f);
			OffsetY -= 1.0f;
			OffsetX += 1.0f;
		}
	}
}

void SDLRenderer::Present()
{
	SDL_RenderPresent(NativeRenderer);
}
