//
//  AScoreManager.h
//  Score Manager.
//
//  Created by Kirill Bravichev on 09/03/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

class AScoreManager
{
public:
	static AScoreManager& Get();

	int32 GetHightScore() const { return HightScore; }
	int32 GetCurrentScore() const { return CurrentScore; }

	void StartGame();
	void UpdateScore(const int32 Score);
	void FinishGame();

private:
	int32 HightScore{ 0 };
	int32 CurrentScore{ 0 };

	AScoreManager();
	~AScoreManager();

	static constexpr FStringView FileName{ "Data/Score" };
};

