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
	Gold,
	Count,
};

class ABlock : public AObject
{
public:
	ABlock(EBlockType Type);
	virtual ~ABlock();

	virtual void Draw(const TSharedPtr<class SDLRenderer>& Renderer) const override;

	virtual void OnCollisionEnter(const TSharedPtr<AObject>& Col) override;
	virtual bool ShouldBeDestroyed() const override { return Settings.Healh == 0; }

	EBlockType GetBlockId() const { return Settings.Type; }
	uint8 GetScore() const { return Settings.Score; }

private:
	struct FBlockSettings
	{
		EBlockType Type;
		uint8 Healh;
		uint8 Score;
		FColor MainColor;
		FColor SecondColor;
	};

	static TFixedArray<const FBlockSettings, static_cast<int32>(EBlockType::Count)> BlockTypes;
	FBlockSettings Settings;
};

