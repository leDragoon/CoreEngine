#include<Game.h>

using namespace std;

bool running = true;
Renderer renderer = Renderer();
AudioHandler soundHandler = AudioHandler();
CoreWindow window = CoreWindow();
ScriptHandler scriptHandler = ScriptHandler();
InputHandler inputHandler = InputHandler();
PhysicsHandler physicsHandler = PhysicsHandler();
SettingsFile programSettings = SettingsFile("settings.ini");
Scene rootScene;

void initSettings();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		rootScene.unload();
		renderer.close();
		soundHandler.close();
		running = false;
		break;
	case WM_SIZE:
		renderer.resize(LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		MSG m;
		m.hwnd = hWnd;
		m.lParam = lParam;
		m.wParam = wParam;
		m.message = msg;

		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initSettings();
	ShowCursor(FALSE);

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	
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

	rootScene.setRenderer(&renderer);
	rootScene.setAudioHandler(&soundHandler);
	rootScene.load("Data//Scenes//root.scn", AssetListFile("Data//globalAssetList.alst").getAssetList());
	rootScene.getCamera()->setFieldOfView(programSettings.getFloat("RENDER", "fieldOfView"));

	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);

	onGameStart(&renderer, &soundHandler, &inputHandler, &physicsHandler, &scriptHandler, &rootScene);

	MSG msg;
	
	while (running)
	{
		MSG m;
		ZeroMemory(&m, sizeof(MSG));
	
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		renderer.render();
		soundHandler.update();
		scriptHandler.update();

		for (unsigned int i = 0; i < scriptHandler.getScriptChanges().names.size(); i++)
		{
			vector<string> sections = separateIntoSections(scriptHandler.getScriptChanges().names[i]);
			vector<string> changeSections = separateIntoSections(scriptHandler.getScriptChanges().changes[i]);;

			if (sections[0] == "m")
			{
				renderer.getObject(sections[1])->translate(XMFLOAT3(stof(changeSections[0]) * renderer.getDeltaTime(), stof(changeSections[1]) * renderer.getDeltaTime(), stof(changeSections[2]) * renderer.getDeltaTime()));
			}
		}

		onTick(&renderer, &soundHandler, &inputHandler, &physicsHandler, &scriptHandler, &rootScene);
	}

	onGameExit(&renderer, &soundHandler, &inputHandler, &physicsHandler, &scriptHandler, &rootScene);
	DestroyWindow(hWnd);
	hWnd = NULL;
	return 0;
}

void initSettings()
{
	window = CoreWindow(programSettings.getCategory("WINDOW"));
}