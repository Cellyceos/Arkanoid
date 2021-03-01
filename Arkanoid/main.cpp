//
//  main.cpp
//  The main entry point to the program.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"

#if USE_SDL
#include "SDL_main.h"
#endif

int main(int argc, char* argv[])
{
	ArkanoidGame Game;

	if (Game.Init())
	{
		return Game.Exec();
	}

	return EXIT_FAILURE;
}
