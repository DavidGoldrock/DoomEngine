#include <windows.h>
#include <commctrl.h>  // Required for toolbar
#include "FileDescriptor.h"
#include <iostream>
#include "WindowFunctions.h"



// Entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetConsoleUp();

    LPCSTR CLASS_NAME = "Doom_Proccessor_Windows_Class";

    if(!RegisterWindowsClass(CLASS_NAME, hInstance)) {
        return -1;
    }

    // Create the window
    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "Doom Reader", // Open a new regular window with the previously created window class
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, // Open in default location with default style
        1920, 1080, NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}