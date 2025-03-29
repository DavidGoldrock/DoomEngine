#include <windows.h>
#include <commctrl.h>  // Required for toolbar
#include "FileDescriptor.h"
#include <iostream>
struct AppData {
    std::shared_ptr<FileDescriptor> fileDescriptor;
};

void AddMenus(HWND hwnd);

#define OPEN_FILE_MENU_ID 1
#define TREE_ID 1001
// Window Procedure: Handles messages sent to the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    AppData* appData = (AppData*)GetWindowLongPtr(hwnd, GWLP_USERDATA); // Retrieve the appData pointer
    switch (uMsg) {
        case WM_CREATE:
            AddMenus(hwnd);
            return 0;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            return 0;
        case WM_LBUTTONDOWN:
            return 0;

        case WM_COMMAND:
            switch(wParam) {
                case OPEN_FILE_MENU_ID:
                    appData->fileDescriptor = FileDescriptor::getFileDescriptorFromUser();
                    return 0;
            }
            return 0;

            case WM_NOTIFY:
            if (((LPNMHDR)lParam)->idFrom == TREE_ID) {
                LPNMTREEVIEW pnmTreeView = (LPNMTREEVIEW)lParam;
                switch (pnmTreeView->hdr.code) {
                    case TVN_SELCHANGED:
                        // Handle selection change
                        return 0;
                    case TVN_ITEMEXPANDING:
                        // Handle item expanding
                        return 0;
                }
            }
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void AddMenus(HWND hwnd) {
    HMENU hMenu = CreateMenu();

    HMENU hFileMenu = CreateMenu();


    AppendMenuA(hFileMenu, MF_POPUP, OPEN_FILE_MENU_ID , "Open");
    AppendMenuA(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
    SetMenu(hwnd, hMenu);
}

// Entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
     // Allocating a new console for the application
    AllocConsole();

    // Redirect the standard output to the console
    freopen("CONOUT$", "w", stdout);
    
    AppData* appData = new AppData();
    appData->fileDescriptor = nullptr;

    // 
    //  Define and set the window class for the window
    //

        // Define a window class (settings for the window)
        WNDCLASSEXA wc = {0}; // Properly zero-out the struct to avoid uninitialized fields
        wc.cbSize = sizeof(WNDCLASSEXA); // Required to specify the size of the struct
        LPCSTR CLASS_NAME = "Doom_Proccessor_Windows_Class";
        wc.lpszClassName = CLASS_NAME;
        wc.lpfnWndProc = WindowProc; // The function to be called to process the window events
        wc.hInstance = hInstance; // Instance of the window
        wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Default cursor, nothing fancy
        wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
        
        // Register the class
        if (!RegisterClassExA(&wc)) {
            // If registration fails, use GetLastError to debug the issue
            DWORD dwError = GetLastError();
            std::cout << "[CLASS REGISTER ERROR #" << dwError << "]" << std::endl;
            // Handle the error or log it (for debugging purposes)
            return 0; // Or some other error handling
        }

    // Create the window
    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "Doom Reader", // Open a new regular window with the previously created window class
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, // Open in default location with default style
        500, 400, NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)appData);

    HWND hwndTreeView = CreateWindowEx(
        0, WC_TREEVIEW, TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_LINESATROOT | TVS_HASBUTTONS,
        10, 10, 300, 400,
        hwnd, (HMENU)TREE_ID, hInstance, nullptr);

    TVINSERTSTRUCT tvis;
    tvis.hParent = TVI_ROOT;  // Root of the tree
    tvis.hInsertAfter = TVI_LAST;  // Insert at the end
    tvis.item.mask = TVIF_TEXT;  // We're inserting text


    // Add root item
    tvis.item.pszText = TEXT("");
    HTREEITEM hRoot = TreeView_InsertItem(hwndTreeView, &tvis);

    // Add a child item
    tvis.hParent = hRoot;
    tvis.item.pszText = TEXT("Sounds");
    TreeView_InsertItem(hwndTreeView, &tvis);
    // Add another child item
    tvis.item.pszText = TEXT("Title Pic");
    TreeView_InsertItem(hwndTreeView, &tvis);
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete appData;

    return 0;
}