//
//  ALevelsManager.h
//  Class for Manage Load Game Levels.
//
//  Created by Kirill Bravichev on 09/03/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/ALevelManager.h"

#include <fstream>
#include <filesystem>


ALevelManager& ALevelManager::Get()
{
	static ALevelManager Context;
	return Context;
}

ALevelManager::ALevelManager()
{
	if (std::filesystem::exists(FileName))
	{
		std::ifstream FileStream(FileName, std::ios::binary);
		if (FileStream.is_open())
		{
			while (FileStream.good())
			{
				int64 Size = 0;
				FileStream.read(reinterpret_cast<char*>(&Size), sizeof(Size));

				TArray<FBlockData> LevelData(Size);
				FileStream.read(reinterpret_cast<char*>(LevelData.data()), Size * sizeof(FBlockData));
				Levels.push_back(LevelData);
			}
		}
	}
}

ALevelManager::~ALevelManager()
{
	SDL_Log("~ALevelManager");
}

TFixedArray<uint16, GameConfig::ColNum* GameConfig::RowNum> ALevelManager::GetLevelSchema(int32 Level)
{
	int32 CurrentIdx = 0;

	TFixedArray<uint16, GameConfig::ColNum* GameConfig::RowNum> UnpackedLevel{};
	for (const auto& BlockData : Levels[Level - 1ll])
	{
		for (int32 Idx = 0; Idx < BlockData.Count; ++Idx)
		{
			UnpackedLevel[CurrentIdx] = BlockData.Type;
			++CurrentIdx;
		}
	}

	return UnpackedLevel;
}