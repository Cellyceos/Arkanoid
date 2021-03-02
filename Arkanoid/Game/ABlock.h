//
//  ABlock.h
//  Block object class.
//
//  Created by Kirill Bravichev on 03/02/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

#include "AObject.h"

class ABlock : public AObject
{
public:
	virtual void Update(float DeltaTime) override;
	virtual void Draw(const TSharedPtr<class IRenderer>& Renderer) const override;
};

