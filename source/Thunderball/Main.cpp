#include "ThunderballApp.h"

#include <windows.h>

// FUNCTION: POPCAPGAME1 0x00431560
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Sexy::ThunderballApp app;
	app.Init();
	app.Start();
	app.Shutdown();
	return 0;
}
