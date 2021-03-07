//
//  GameConfig.h
//  Arkanoid Game.
//
//  Created by Kirill Bravichev on 03/06/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

class GameConfig
{
public:
	static constexpr int32 WindowWidth{ 1024 };
	static constexpr int32 WindowHeight{ 768 };
	static constexpr FStringView WindowTitle{ "Arkanoid Game" };

	static constexpr float BorderSize{ 10.0f };
	static constexpr float LevelRatio{ 2.0f/3.0f };
	static constexpr float UserInterfaceRatio{ 1.0f/3.0f };
};