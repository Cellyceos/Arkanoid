//
//  FixedFrameRate.h
//  Frame rate control.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"

#include <chrono>

class AFixedFrameRate
{
public:
	AFixedFrameRate(int64 Rate);

	void WaitForFixedRate() const;

	float GetDeltaTime() const;

	void SetFixedRate(int64 Rate);
	int64 GetFixedRate() const { return FixedRate; }

private:
	int64 FixedRate = 60ll;
	int64 FrameTime = 0ll;

	mutable std::chrono::time_point<std::chrono::high_resolution_clock> TimeStamp;
};

