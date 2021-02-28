//
//  main.cpp
//  The main entry point to the program.
//
//  Created by Kirill Bravichev on 02/27/2021.
//  Copyright (c) 2021 Cellyceos. All rights reserved.
//

#include "ArkanoidGame.h"

int Execute()
{
	ArkanoidGame Game;

	if (Game.Init())
	{
		return Game.Exec();
	}

	return EXIT_FAILURE;
}

#if _CONSOLE
int main(int argc, char* argv[])
{
	return Execute();
}
#elif _WINDOWS
// Windows Header Files
#include <windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	return Execute();
}
#endif
