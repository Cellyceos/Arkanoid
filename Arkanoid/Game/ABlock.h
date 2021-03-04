//
//  ABlock.h
//  Block object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "AObject.h"

enum class EBlockType
{
	Unknown,
	White,
	Orange,
	LightBlue,
	Green,
	Red,
	Blue,
	Pink,
	Yellow,
	Silver,
	Gold
};

class ABlock : public AObject
{
public:
	ABlock(EBlockType Type);

	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class IRenderer>& Renderer) const override;

private:
	struct FBlockSettings
	{
		uint8 Healh;
		FColor MainColor;
		FColor SecondColor;
	};

	static TUnorderedMap<EBlockType, FBlockSettings> BlockTypes;
	FBlockSettings Settings;
};

