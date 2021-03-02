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
	FrameTime = std::nano::den / Rate;
	FixedRate = Rate;
}

void AFixedFrameRate::WaitForFixedRate() const
{
	const auto CurrentTime = std::chrono::high_resolution_clock::now();
	const auto WaitTime = FrameTime - (CurrentTime - TimeStamp).count();
	if (WaitTime > 0)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(WaitTime));
	}

	TimeStamp = std::chrono::high_resolution_clock::now();
}

float AFixedFrameRate::GetDeltaTime() const
{
	return static_cast<float>(FrameTime) / std::nano::den;
}
