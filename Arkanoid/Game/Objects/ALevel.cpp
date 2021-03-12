//
//  Level.cpp
//  Manages all objects at the level.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "Objects/ALevel.h"
#include "Objects/ABall.h"
#include "Objects/ABlock.h"
#include "Objects/APlatform.h"

#include "Game/AScoreManager.h"
#include "Game/ALevelManager.h"


ALevel::ALevel()
{
	Platform = std::make_shared<APlatform>();
	Ball = std::make_shared<ABall>();
}

ALevel::~ALevel()
{
	AScoreManager::Get().FinishGame();
}

bool ALevel::StartGame(int32 InLevel /* = 1 */)
{
	ALevelManager& LevelManager = ALevelManager::Get();
	if (InLevel > LevelManager.GetLevelCount())
	{
		return false;
	}

	Level = InLevel;

	Platform->SetCenterPoint({ Position.X + Aabb.Radius[0], Size.Height - Platform->GetHeight() });
	Ball->SetCenterPoint({ Position.X + Aabb.Radius[0], Size.Height - Platform->GetHeight() - Ball->GetHeight() });
	Ball->AttachTo(Platform);

	const float Offset = 2.0;
	const float X = Position.X + BorderSize + Offset;
	const float Y = Position.Y + BorderSize + Offset;
	const float BrickWidth = (Size.Width - 2.0f * BorderSize - Offset) / GameConfig::ColNum;
	const float BrickHeight = (Size.Height - 2.0f * BorderSize - Offset) / GameConfig::RowNum;

	const auto& LevelSchema = LevelManager.GetLevelSchema(Level);
	for (uint64 Idx = 0ll; Idx < GameConfig::ColNum * GameConfig::RowNum; Idx++)
	{
		const EBlockType BlockType = static_cast<EBlockType>(LevelSchema[Idx]);
		if (BlockType != EBlockType::Unknown)
		{
			auto Block = std::make_shared<ABlock>(BlockType);
			Block->SetRect({ (X + (Idx % GameConfig::ColNum) * BrickWidth), (Y + (Idx / GameConfig::ColNum) * BrickHeight), BrickWidth - Offset, BrickHeight - Offset });
			StaticObjects[Idx] = Block;
			++AliveBlocksCount;
		}
	}

	return true;
}

void ALevel::SetRect(const FRect& Rect)
{
	AObject::SetRect({ Rect.X + BorderSize, Rect.Y + BorderSize, Rect.Width - 2.0f * BorderSize, Rect.Height - 2.0f * BorderSize });
}

void ALevel::SetupPlayerInput(const TSharedPtr<class IInputHandler>& InputHandler)
{
	Platform->SetupPlayerInput(InputHandler);
}

void ALevel::Update(float DeltaTime)
{
	Platform->Update(DeltaTime);
	ShouldBeInside(Platform);

	Ball->Update(DeltaTime);
	ShouldBeInside(Ball);

	if (Ball->ShouldBeDestroyed())
	{
		Platform->SetCenterPoint({ Position.X + Aabb.Radius[0], Size.Height - Platform->GetHeight() });
		Ball->SetCenterPoint({ Position.X + Aabb.Radius[0], Size.Height - Platform->GetHeight() - Ball->GetHeight() });
		Ball->AttachTo(Platform);
		--CurrentLives;
	}

	CheckCollision();
}

void ALevel::CheckCollision()
{
	const FAABB& BallAabb = Ball->GetAABB();
	if (BallAabb.Test(Platform->GetAABB()))
	{
		Ball->OnCollisionEnter(Platform);
		Platform->OnCollisionEnter(Ball);
		return;
	}

	for (auto ObjIter = StaticObjects.rbegin(); ObjIter != StaticObjects.rend(); ++ObjIter)
	{
		auto& Obj = *ObjIter;
		if (Obj && BallAabb.Test(Obj->GetAABB()))
		{
			Obj->OnCollisionEnter(Ball);
			Ball->OnCollisionEnter(Obj);

			if (Obj->ShouldBeDestroyed())
			{
				int32 Score = Obj->GetScore();
				if (Obj->GetBlockId() == EBlockType::Silver)
				{
					Score *= Level;
				}

				AScoreManager::Get().UpdateScore(Score);
				--AliveBlocksCount;
				Obj.reset();
			}

			break;
		}
	}
}

void ALevel::ShouldBeInside(const TSharedPtr<AObject>& Obj)
{
	bool bCollided = false;

	const FAABB& ObjAABB = Obj->GetAABB();
	FPoint Center{ ObjAABB.Center };

	const float HalfWidth = ObjAABB.Radius[0];
	const float HalfHeight = ObjAABB.Radius[1];

	const float Right = Position.X + Size.Width;
	const float Bottom = Position.Y + Size.Height;

	if ((ObjAABB.Center.X - HalfWidth) < Position.X)
	{
		Center.X = Position.X + HalfWidth;
		bCollided = true;
	}
	else if ((ObjAABB.Center.X + HalfWidth) > Right)
	{
		Center.X = Right - HalfWidth;
		bCollided = true;
	}

	if ((ObjAABB.Center.Y - HalfHeight) < Position.Y)
	{
		Center.Y = Position.Y + HalfHeight;
		bCollided = true;
	}
	else if ((ObjAABB.Center.Y + HalfHeight) >= Bottom)
	{
		Center.Y = Bottom - HalfHeight;
		bCollided = true;
	}

	if (bCollided)
	{
		Obj->SetCenterPoint(Center);
		Obj->OnCollisionEnter(shared_from_this());
	}
}


void ALevel::Draw(const TSharedPtr<SDLRenderer>& Renderer) const
{
	Renderer->SetColor(BorderColor);
	Renderer->FillRect({ Position.X - BorderSize, Position.Y - BorderSize, BorderSize, Size.Height + 2.0f * BorderSize });
	Renderer->FillRect({ Position.X - BorderSize, Position.Y - BorderSize, Size.Width + 2.0f * BorderSize, BorderSize });
	Renderer->FillRect({ Position.X + Size.Width, Position.Y - BorderSize, BorderSize, Size.Height + 2.0f * BorderSize });
	Renderer->FillRect({ Position.X - BorderSize, Position.Y + Size.Height, Size.Width + 2.0f * BorderSize, BorderSize });

	for (const auto& Obj : StaticObjects)
	{
		if (Obj)
		{
			Obj->Draw(Renderer);
		}
	}

	Ball->Draw(Renderer);
	Platform->Draw(Renderer);
}
