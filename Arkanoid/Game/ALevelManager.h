//
//  ALevelsManager.h
//  Class for Manage Load Game Levels.
//
//  Created by Kirill Bravichev on 09/03/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameConfig.h"


struct FBlockData
{
	uint16 Count : 10;
	uint16 Type : 6;
};

class ALevelManager
{
public:
	static ALevelManager& Get();

	int64 GetLevelCount() const { return Levels.size(); }
	TFixedArray<uint16, GameConfig::ColNum * GameConfig::RowNum> GetLevelSchema(int32 Level);

private:
	ALevelManager();
	~ALevelManager();

	TArray<TArray<FBlockData>> Levels;

	static constexpr FStringView FileName{ "Assets/Levels" };
};

