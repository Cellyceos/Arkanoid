//
//  SDLContext.h
//  Context for correctly init and deinit SDL lib.
//
//  Created by Kirill Bravichev on 02/28/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#pragma once

class SDLContext
{
public:
	static SDLContext& Get() { return Context; }

private:
	SDLContext();
	~SDLContext();

	static SDLContext Context;
};
