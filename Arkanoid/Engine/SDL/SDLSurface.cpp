//
//  SDLSurface.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLSurface.h"
#include "Logging/Macros.h"

#include "SDL_surface.h"


SDLSurface::SDLSurface(SDL_Surface* SurfacePtr) : NativeSurface(SurfacePtr)
{
	// Enable Alpha Blending by default
	SDL_SetSurfaceBlendMode(NativeSurface, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceRLE(NativeSurface, true);
}

int32 SDLSurface::GetWidth() const
{
	return NativeSurface->w;
}

int32 SDLSurface::GetHeight() const
{
	return NativeSurface->h;
}

EPixelFormatType SDLSurface::GetFormat() const {
	return static_cast<EPixelFormatType>(NativeSurface->format->format);
}

void SDLSurface::SetColorPalette(const TSharedPtr<APaletteClass>& Palette)
{
	SDL_SetSurfacePalette(NativeSurface, Palette->GetNativePalette());
}

SDLSurface::~SDLSurface()
{
	if (NativeSurface)
	{
		SDL_FreeSurface(NativeSurface);
		NativeSurface = nullptr;
	}

	LOG("~SDLSurface\n");
}

TSharedPtr<SDLSurface> SDLSurface::Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth,
	uint32 RedMask /* = 0u */, uint32 GreenMask /* = 0u */, uint32 BlueMask /* = 0u */, uint32 AlphaMask /* = 0u */)
{
	if (SDL_Surface* NativeSurface = SDL_CreateRGBSurface(0, Width, Height, Depth, RedMask, GreenMask, BlueMask, AlphaMask))
	{
		SDL_LockSurface(NativeSurface);
		std::memcpy(NativeSurface->pixels, Pixels.data(), Pixels.size());
		SDL_UnlockSurface(NativeSurface);

		return std::make_shared<SDLSurface>(NativeSurface);
	}

	LOG_CRITICAL("Unable to create surface, error: %s", SDL_GetError());
	return nullptr;
}

TSharedPtr<SDLSurface> SDLSurface::Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth, EPixelFormatType PixelFormat)
{
	if (SDL_Surface* NativeSurface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, Depth, static_cast<uint32>(PixelFormat)))
	{
		SDL_LockSurface(NativeSurface);
		std::memcpy(NativeSurface->pixels, Pixels.data(), Pixels.size());
		SDL_UnlockSurface(NativeSurface);

		return std::make_shared<SDLSurface>(NativeSurface);
	}

	LOG_CRITICAL("Unable to create surface, error: %s", SDL_GetError());
	return nullptr;
}

#ifdef USE_SDL_IMG
#include "SDL_image.h"

static TSharedPtr<SDLSurface> SDLSurface::Construct(const FStringView& ImageName)
{
	if (SDL_Surface* NativeSurface = IMG_Load(ImageName.data()))
	{
		return std::make_shared<SDLSurface>(NativeSurface);
	}

	LOG_CRITICAL("Unable to load image, error: %s", SDL_GetError());
	return nullptr;
}
#endif
