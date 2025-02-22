/*
	MODULE: terminal.c

	PURPOSE: Program's main entry point

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#include "terminal.h"

// Private variables
TCHAR	szAppName[] = TEXT("Terminal Emulator, Assignment #2");

// Private function prototypes
BOOL InitApp(HINSTANCE, int);
BOOL VersionCheck();

/*
	FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

	PURPOSE: Start application and process all window messages

	PARAMETERS:
		hInstance		- this application's instance
		hPrevInstance	- previous instance of this application (always NULL)
		lpCmdLine		- command line parameters
		nCmdShow		- code for showing the window

	RETURN:
		1 for success
		0 for failure to start the application
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;

	// Verify that the program can run on this version of windows
	if (!VersionCheck()) {
		MessageBox(NULL, "Terminal cannot run on this version of Windows.",
			NULL, MB_OK | MB_ICONSTOP);
		return 0;
	}

	// Attempt to initialize the application and create the main window and class
	if (!InitApp(hInstance, nCmdShow)) {
		MessageBox(NULL, "Terminal couldn't start! We don't know why, it just couldn't!",
			NULL, MB_OK | MB_ICONSTOP);
	}

	// Main message loop
	while (GetMessage(&msg, NULL, 0, 0)) {	// Get message from queue
		// Send message to accelerator to check if it is a keyboard command
		if (!TranslateAccelerator(ghWnd, ghAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;	// Exit parameter to be returned to the OS
}

/*
	FUNCTION: VersionCheck(void)

	PURPOSE: Verifies that the correct version of Windows is running

	RETURN:
		TRUE	- successful initialization of this application
		FALSE	- failure to initilaize the application
*/
BOOL VersionCheck() {
	gOSV.dwOSVersionInfoSize = sizeof(gOSV);
	if (!GetVersionEx(&gOSV)) {
		return FALSE;
	}

	if (gOSV.dwPlatformId == VER_PLATFORM_WIN32s) {
		return FALSE;
	}

	return TRUE;
}

/*
	FUNCTION: InitApp(HINSTANCE hInst, int nCmdShow)

	PURPOSE: Register window classes and create the main window

	PARAMETERS:
		hInst		- HINSTANCE for this application
		nCmdShow	- Code for showing this window

	RETURN:
		TRUE	- successful initialization of this application
		FALSE	- failure to initialize application

*/
BOOL InitApp(HINSTANCE hInst, int nCmdShow) {
	WNDCLASS	wc;

	// Setup the program's main window class
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= TermWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInst;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName	= szAppName;

	// Register wndclass to OS so appropriate window messages are sent to the application.
	if (!RegisterClass(&wc)) {
		return FALSE;
	}
	
	// Create the main window
	ghWnd = CreateWindow(szAppName, "Terminal Emulator",
		WS_OVERLAPPEDWINDOW,
		X_START_POS, Y_START_POS,
		X_SIZE, Y_SIZE,
		NULL, NULL, hInst, NULL);

	// Show the main window
	ShowWindow(ghWnd, nCmdShow);
	UpdateWindow(ghWnd);

	ghInst = hInst;	// set the global instance for this program

	// set the global instance for the keyboard accelerator
	ghAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	return TRUE;
}