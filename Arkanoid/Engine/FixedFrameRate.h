//
//  FixedFrameRate.h
//  Frame rate control.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "BasicTypes.h"

#include <chrono>

class AFixedFrameRate
{
public:
	AFixedFrameRate(int64 Rate = 0ll);

	void WaitForFixedRate() const;

	float GetDeltaTime() const;

	void SetFixedRate(int64 Rate);
	int64 GetFixedRate() const { return FixedRate; }

	bool IsFrameRateLocked() const { return FixedRate > 0; }

	int64 GetCurrentFrameRate() const { return OneSecond / DeltaTime; }

private:
	std::chrono::nanoseconds FixedFrameTime;
	int64 FixedRate;

	static constexpr std::chrono::nanoseconds OneSecond{ std::chrono::seconds(1) };

	mutable std::chrono::nanoseconds DeltaTime{ std::chrono::nanoseconds::zero() };
	mutable std::chrono::time_point<std::chrono::high_resolution_clock> TimeStamp{  };
};

