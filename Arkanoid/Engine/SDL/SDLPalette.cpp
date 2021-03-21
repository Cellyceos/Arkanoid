//
//  SDLPalette.cpp
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/16/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "SDL/SDLPalette.h"
#include "Logging/Macros.h"

#include "SDL_pixels.h"


SDLPalette::SDLPalette(SDL_Palette* PalettePtr) : NativePalette(PalettePtr)
{

}

SDLPalette::~SDLPalette()
{
	if (NativePalette)
	{
		SDL_FreePalette(NativePalette);
		NativePalette = nullptr;
	}

	LOG("~SDLPalette\n");
}

TSharedPtr<SDLPalette> SDLPalette::Construct(const TArray<uint8>& Colors)
{
	const int32 NumberColors = static_cast<int32>(Colors.size() >> 2);
	if (SDL_Palette* NativePalette = SDL_AllocPalette(NumberColors))
	{
		SDL_SetPaletteColors(NativePalette, reinterpret_cast<const SDL_Color*>(Colors.data()), 0, NumberColors);
		return std::make_shared<SDLPalette>(NativePalette);
	}

	return nullptr;
}