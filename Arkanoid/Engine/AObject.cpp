//
//  AObject.cpp
//  Base Class for All object in the game.
//
//  Created by Kirill Bravichev on 03/01/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "AObject.h"

void AObject::SetRect(const FRect& Rect) 
{ 
	Position = { Rect.X, Rect.Y }; 
	Size = { Rect.Width, Rect.Height }; 
}

void AObject::SetSize(const FSize& NewSize) 
{ 
	Size = NewSize; 
	Aabb.Radius = { NewSize.Width * 0.5f, NewSize.Height * 0.5f };
}

void AObject::SetCenterPoint(const FPoint& Point) 
{ 
	Position = { Point.X - Aabb.Radius[0], Point.Y - Aabb.Radius[1] };
	Aabb.Center = Point;
}
