#include<iostream>
#include<WindowManager.h>
#include<Renderer.h>
#include<SettingsFile.h>
#include<Scene.h>

using namespace std;

bool running = true;
Renderer renderer;
CoreWindow window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		running = false;
		break;
	case WM_SIZE:
		renderer.resize(LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SettingsFile programSettings = SettingsFile("settings.ini");
	window = CoreWindow(programSettings.getCategory("WINDOW"));
	
	WNDCLASSEX wClass;
	
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = NULL;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = (HICON)LoadImage(NULL, "Icon.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE | LR_SHARED);
	wClass.hIconSm = (HICON)LoadImage(NULL, "Icon.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE | LR_SHARED);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WndProc;
	wClass.lpszClassName = "wClass";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Could not register window class", "Window Creation Error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	HWND hWnd = CreateWindowEx(NULL, "wClass", window.getWindowTitle().c_str(), WS_OVERLAPPEDWINDOW, window.getWindowPosition().x, window.getWindowPosition().y, window.getWindowSize().x, window.getWindowSize().y, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, "Could not create window", "Window creation error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	window.setHandle(hWnd);
	renderer = Renderer(window);
	renderer.init();
	Scene rootScene;
	rootScene.setRenderer(&renderer);
	rootScene.load("Data//Scenes//root.scn", AssetListFile("Data//globalAssetList.alst").getAssetList());

	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);

	MSG msg;
	
	while (running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		renderer.render();
	}

	rootScene.unload();
	renderer.close();
	DestroyWindow(hWnd);
	hWnd = NULL;
	return 0;
}