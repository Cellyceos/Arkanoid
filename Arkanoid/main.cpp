//
//  main.cpp
//  The main entry point to the program.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"
#include "SDL_main.h"


int main(int argc, char* argv[])
{
	ArkanoidGame Game;

	if (Game.Init())
	{
		return Game.Loop();
	}

	return EXIT_FAILURE;
}
