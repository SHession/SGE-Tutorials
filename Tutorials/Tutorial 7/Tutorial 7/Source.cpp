#include <Windows.h>
#include "Game1.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
	Game1 game;
	SGE::Framework::GameDescription GD;
	GD.fullscreen = true;
	GD.height = 1080;
	GD.width = 1920;

	HRESULT result = game.Run(NULL,hInstance,nCmdShow);

}