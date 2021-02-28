//
//  IRenderer.h
//  Base Wrapper Interface Class.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//
#pragma once

#include "CoreMinimal.h"

class IRenderer
{
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;

	virtual void Clear(const FColor& Color) = 0;
	virtual void Present() = 0;
};
