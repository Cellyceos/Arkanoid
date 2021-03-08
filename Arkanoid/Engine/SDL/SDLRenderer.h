//
//  SDLRenderer.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"


enum class ETextJustify {
	LeftTop,
	LeftMiddle, 
	LeftBottom,
	CenteredTop,
	CenteredMiddle,
	CenteredBottom,
	RightTop,
	RightMiddle,
	RightBottom
};

struct FFontKey
{
	FStringView FontName;
	int32 FontSize;

	friend bool operator <(const FFontKey& Left, const FFontKey& Right)
	{
		if (Left.FontName == Right.FontName)
		{
			return Left.FontSize < Right.FontSize;
		}

		return Left.FontSize > Right.FontSize && Left.FontName < Right.FontName;
	}
};

class SDLRenderer
{
public:
	explicit SDLRenderer(struct SDL_Renderer* RendererPtr);
	virtual ~SDLRenderer();

	static TSharedPtr<SDLRenderer> Construct(struct SDL_Window* Window);

	virtual void Clear(const FColor& Color);
	virtual void Present();

	virtual void SetColor(const FColor& Color);
	virtual void SetFont(const FStringView& FontName, const int32 FontSize);

	// Rectangle
	virtual void DrawRect(const FRect& Rect);
	virtual void FillRect(const FRect& Rect);

	// Circle
	virtual void DrawCircle(const FPoint& Center, float Radius);
	virtual void FillCircle(const FPoint& Center, float Radius);

	// Text
	virtual void DrawText(const FStringView& Text, const FPoint& Position, ETextJustify Justify, const FColor& Color);

	virtual struct SDL_Renderer* GetNativeRenderer() const { return NativeRenderer; }

private:
	struct SDL_Renderer* NativeRenderer = nullptr;
	struct _TTF_Font* CurrentFont = nullptr;

	static TMap <FFontKey, struct _TTF_Font*> FontNameCache;

#ifdef _DEBUG
	static FColor DebugColor;
#endif // _DEBUG
};

using ARendererClass = SDLRenderer;
