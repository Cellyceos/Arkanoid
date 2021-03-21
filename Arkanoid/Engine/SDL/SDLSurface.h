//
//  SDLSurface.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 03/15/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"
#include "SDL/SDLPalette.h"

#include "SDL_pixels.h"


enum class EPixelFormatType
{
    Unknown = SDL_PIXELFORMAT_UNKNOWN,
    Mono = SDL_PIXELFORMAT_INDEX1MSB,
    MonoLSB = SDL_PIXELFORMAT_INDEX1LSB,
    Indexed8 = SDL_PIXELFORMAT_INDEX8,
    RGB32 = SDL_PIXELFORMAT_RGB888,
    ARGB32 = SDL_PIXELFORMAT_ARGB32,
    RGB16 = SDL_PIXELFORMAT_RGB565,
    RGB555 = SDL_PIXELFORMAT_RGB555,
    RGB888 = SDL_PIXELFORMAT_RGB888,
    RGB444 = SDL_PIXELFORMAT_RGB444,
    ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
    RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
    RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
    BGR24 = SDL_PIXELFORMAT_BGR24,
    RGB24 = SDL_PIXELFORMAT_RGB24,
};


class SDLSurface : public std::enable_shared_from_this<SDLSurface>
{
public:
    explicit SDLSurface(struct SDL_Surface* SurfacePtr);
    virtual ~SDLSurface();

    int32 GetWidth() const;
    int32 GetHeight() const;

    EPixelFormatType GetFormat() const;
    void SetColorPalette(const TSharedPtr<APaletteClass>& Palette);

    struct SDL_Surface* GetNativeSurface() const { return NativeSurface; }

    static TSharedPtr<SDLSurface> Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth, uint32 RedMask = 0u, uint32 GreenMask = 0u, uint32 BlueMask = 0u, uint32 AlphaMask = 0u);
    static TSharedPtr<SDLSurface> Construct(const TArray<uint8>& Pixels, int32 Width, int32 Height, int32 Depth, EPixelFormatType PixelFormat);

private:
    friend class SDLRenderer;
    struct SDL_Surface* NativeSurface = nullptr;

#ifdef USE_SDL_IMG
public:
    static TSharedPtr<SDLSurface> Construct(const FStringView& ImageName);
#endif
};

using ASurfaceClass = SDLSurface;
