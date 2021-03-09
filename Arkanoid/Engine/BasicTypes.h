//
//  BasicTypes.h
//  Basic types for project.
//
//  Created by Kirill Bravichev on 03/07/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include <cstdint>
#include <memory>

#include <string>
#include <string_view>

#include <array>
#include <vector>

#include <map>
#include <unordered_map>

#include <functional>

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

template<class T> using TUniquePtr = std::unique_ptr<T>;
template<class T> using TSharedPtr = std::shared_ptr<T>;
template<class T> using TWeakPtr = std::weak_ptr<T>;

using FString = std::string;
using FStringView = std::string_view;

template<class Key, class T> using TMap = std::map<Key, T>;
template<class Key, class T> using TUnorderedMap = std::unordered_map<Key, T>;

template<typename T> using TArray = std::vector<T>;
template<typename T, uint64 Size> using TFixedArray = std::array<T, Size>;

using namespace std::placeholders;
template<typename T> using TFunction = std::function<T>;

struct FColor
{
	uint8 Red = 0;
	uint8 Green = 0;
	uint8 Blue = 0;
	uint8 Alpha = 0;
};

struct FPoint
{
	float X = 0.0f;
	float Y = 0.0f;
};

struct FSize
{
	float Width = 0.0f;
	float Height = 0.0f;
};

struct FRect
{
	float X = 0.0f;
	float Y = 0.0f;
	float Width = 0.0f;
	float Height = 0.0f;

	FRect() = default;
	FRect(const float InX, const float InY, const float InWidth, const float InHeight) : X(InX), Y(InY), Width(InWidth), Height(InHeight) { }
	FRect(const FPoint& Point, const FSize& Size) : X(Point.X), Y(Point.Y), Width(Size.Width), Height(Size.Height) { }

	float GetLeft() const { return X; }
	float GetTop() const { return Y; }
	float GetRight() const { return X + Width; }
	float GetBottom() const { return Y + Height; }

	bool IntersectsWith(const FRect& rect) const
	{
		return (GetLeft() < rect.GetRight() && GetTop() < rect.GetBottom() && GetRight() > rect.GetLeft() && GetBottom() > rect.GetTop());
	}
};

struct FAABB
{
	FPoint Center;
	TFixedArray<float, 2> Radius{ 0.0f, 0.0f };

	bool Test(const FAABB& Other) const
	{
		if (std::fabsf(Center.X - Other.Center.X) > (Radius[0] + Other.Radius[0])) return false;
		if (std::fabsf(Center.Y - Other.Center.Y) > (Radius[1] + Other.Radius[1])) return false;
		return true;
	}
};

enum class EInputEvent
{
	Released,
	Pressed
};

using FInputDelegate = TFunction<void(EInputEvent)>;
