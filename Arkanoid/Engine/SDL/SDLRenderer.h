//
//  SDLRenderer.h
//  Wrapper class for SDL.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IRenderer.h"

class SDLRenderer : public IRenderer
{
public:
	explicit SDLRenderer(struct SDL_Renderer* RendererPtr);
	virtual ~SDLRenderer();

	static TSharedPtr<SDLRenderer> Construct(struct SDL_Window* Window);

	virtual void Clear(const FColor& Color) override;
	virtual void Present() override;

	virtual void SetColor(const FColor& Color) override;

	virtual void DrawRect(const FRect& Rect) override;
	virtual void FillRect(const FRect& Rect) override;

	virtual void DrawCircle(const FPoint& Center, float Radius) override;
	virtual void FillCircle(const FPoint& Center, float Radius) override;

	virtual void* GetNativeRenderer() const override { return NativeRenderer; }

private:
	struct SDL_Renderer* NativeRenderer = nullptr;
};
