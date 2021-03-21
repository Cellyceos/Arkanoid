//
//  SDLPalette.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/16/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"


class SDLPalette
{
public:
	explicit SDLPalette(struct SDL_Palette* PalettePtr);
	virtual ~SDLPalette();

	struct SDL_Palette* GetNativePalette() const { return NativePalette; }

	static TSharedPtr<SDLPalette> Construct(const TArray<uint8>& Colors);

private:
	struct SDL_Palette* NativePalette = nullptr;
};

using APaletteClass = SDLPalette;
