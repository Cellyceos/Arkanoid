//
//  CoreMinimal.h
//  Common data types and methods for project.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include <cstdint>
#include <memory>

#include <string>
#include <string_view>

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

template<class T> using UniquePtr = std::unique_ptr<T>;
template<class T> using SharedPtr = std::shared_ptr<T>;
template<class T> using WeakPtr = std::weak_ptr<T>;

using String = std::string;
using StringView = std::string_view;

template <class T, class... Types>
UniquePtr<T> MakeUnique(Types&&... Args) { return std::make_unique<T>(std::forward<Types>(Args)...); }

template <class T, class... Types>
SharedPtr<T> MakeShared(Types&&... Args) { return std::make_shared<T>(std::forward<Types>(Args)...); }

struct FColor
{
	uint8 Red = 0;
	uint8 Green = 0;
	uint8 Blue = 0;
	uint8 Alpha = 0;
};

struct FPoint
{
	int32 X = 0;
	int32 Y = 0;
};

struct FRect
{
	int32 X = 0;
	int32 Y = 0;
	int32 Width = 0;
	int32 Height = 0;
};
