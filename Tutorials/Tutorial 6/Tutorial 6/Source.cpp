#include <Windows.h>
#include "Game1.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
	Game1 game;
	HRESULT result = game.Run(NULL,hInstance,nCmdShow);

}