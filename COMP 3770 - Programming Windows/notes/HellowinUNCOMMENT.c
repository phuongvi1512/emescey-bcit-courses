#include <windows.h>
#include <mmsystem.h>

LRESULT CALLBACK HelloWndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	HWND	hwnd;
	MSG		msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra	= 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass (&wndclass)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT"),
					szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,		
						TEXT("Hello World for Windows"), 
						WS_OVERLAPPEDWINDOW,	
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						NULL,				
						NULL,				
						hInstance,			
						NULL);				

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	PAINTSTRUCT ps;
	RECT	rect;

	switch (message){
		case WM_CREATE:
			PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);

			DrawText(hdc, TEXT("Hello, Windows"), -1, &rect,
					DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
