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
	SetSize({ Rect.Width, Rect.Height });
	SetPosition({ Rect.X, Rect.Y });
}

void AObject::SetSize(const FSize& NewSize) 
{ 
	Size = NewSize; 
	Aabb.Radius = { NewSize.Width * 0.5f, NewSize.Height * 0.5f };
}

void AObject::SetPosition(const FPoint& NewPos)
{ 
	Position = NewPos; 
	Aabb.Center = { Position.X + Aabb.Radius[0], Position.Y + Aabb.Radius[1] };
}

void AObject::SetCenterPoint(const FPoint& Point) 
{ 
	Position = { Point.X - Aabb.Radius[0], Point.Y - Aabb.Radius[1] };
	Aabb.Center = Point;
}
