//
//  FixedFrameRate.cpp
//  Frame rate control.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "FixedFrameRate.h"

#include <thread>

AFixedFrameRate::AFixedFrameRate(int64 Rate)
{
	SetFixedRate(Rate);

	TimeStamp = std::chrono::high_resolution_clock::now();
}

void AFixedFrameRate::SetFixedRate(int64 Rate)
{
	FixedRate = Rate;
	if (Rate > 0)
	{
		FixedFrameTime = OneSecond / Rate;
	}
}

void AFixedFrameRate::WaitForFixedRate() const
{
	const auto CurrentTime = std::chrono::high_resolution_clock::now();
	DeltaTime = CurrentTime - TimeStamp;

	if (FixedRate > 0)
	{
		const auto WaitTime = FixedFrameTime - DeltaTime;
		DeltaTime += WaitTime;

		if (WaitTime > std::chrono::nanoseconds::zero())
		{
			std::this_thread::sleep_for(WaitTime);
		}
	}

	TimeStamp = std::chrono::high_resolution_clock::now();
}

float AFixedFrameRate::GetDeltaTime() const
{
	return DeltaTime.count() / static_cast<float>(std::nano::den);
}
