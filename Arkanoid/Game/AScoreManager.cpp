//
//  AScoreManager.cpp
//  Score Manager.
//
//  Created by Kirill Bravichev on 09/03/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Game/AScoreManager.h"

#include <fstream>
#include <filesystem>


AScoreManager& AScoreManager::Get()
{
	static AScoreManager Context;
	return Context;
}

AScoreManager::AScoreManager()
{
	if (std::filesystem::exists(FileName))
	{
		std::ifstream FileStream(FileName, std::ios::binary);
		if (FileStream.is_open())
		{
			FileStream >> HightScore;
		}
	}
}

AScoreManager::~AScoreManager()
{
	SDL_Log("~AScoreManager");
	std::ofstream FileStream(FileName, std::ios::binary);
	if (FileStream.is_open())
	{
		FileStream << HightScore;
	}
}

void AScoreManager::StartGame()
{
	CurrentScore = 0;
}

void AScoreManager::UpdateScore(const int32 Score)
{
	CurrentScore += Score;
}

void AScoreManager::FinishGame()
{
	if (CurrentScore > HightScore)
	{
		HightScore = CurrentScore;
	}
}
