#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <windows.h>
#include <commctrl.h>
#include "AppData.h"
// Forward declarations
struct AppData;

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hwnd);
void CreateProgram(AppData* appData, HWND hwnd);
void HandleMenuEvent(AppData* appData, WPARAM wParam, HWND hwnd);
void HandleTreeviewEvent(AppData* appData, LPARAM lParam);
bool RegisterWindowsClass(LPCSTR CLASS_NAME, HINSTANCE hInstance);
HWND ConstructTreeview(AppData *appData, HWND hwnd, HINSTANCE hInstance);
int GetTreeViewItemDepth(HWND hTreeView, HTREEITEM hItem);
std::string GetTreeViewItemName(HWND hTreeView, HTREEITEM hItem);
void SetConsoleUp();

// Optional: if you use std::cout inside RegisterClass
#include <iostream>

#endif // APP_WINDOW_H