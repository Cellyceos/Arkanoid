//
//  SDLRenderer.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/GenericRenderer.h"

enum class ETextJustify {
	CenteredTop,
	CenteredMid,
	CenteredBottom
};

struct FFontKey
{
	FStringView FontName;
	int32 FontSize;

	friend bool operator <(const FFontKey& Left, const FFontKey& Right)
	{
		if (Left.FontSize < Right.FontSize)
		{
			return true;
		}

		return Left.FontName < Right.FontName;
	}
};

class SDLRenderer : public AGenericRenderer
{
public:
	explicit SDLRenderer(struct SDL_Renderer* RendererPtr);
	virtual ~SDLRenderer();

	static TSharedPtr<SDLRenderer> Construct(struct SDL_Window* Window);

	virtual void Clear(const FColor& Color) override;
	virtual void Present() override;

	virtual void SetColor(const FColor& Color) override;
	virtual void SetFont(const FStringView& FontName, const int32 FontSize);

	// Rectangle
	virtual void DrawRect(const FRect& Rect) override;
	virtual void FillRect(const FRect& Rect) override;

	// Circle
	virtual void DrawCircle(const FPoint& Center, float Radius) override;
	virtual void FillCircle(const FPoint& Center, float Radius) override;

	// Text
	virtual void DrawText(const FStringView& Text, const FPoint& Position, ETextJustify Justify, const FColor& Color);

	virtual void* GetNativeRenderer() const override { return NativeRenderer; }

private:
	struct SDL_Renderer* NativeRenderer = nullptr;
	struct _TTF_Font* CurrentFont = nullptr;

	static TMap <FFontKey, struct _TTF_Font*> FontCache;
};
