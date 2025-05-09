#include "WindowFunctions.h"
#include <string>
#include <vector>
#include <sstream>
#include <codecvt>  // for std::wstring_convert
#include <locale>
#include <commctrl.h>
#include <mmsystem.h>
#include <thread>

#pragma comment(lib, "winmm.lib")

#define OPEN_FILE_MENU_ID 1
#define CLOSE_FILE_MENU_ID 2
#define PLAY_BUTTON_ID 3
#define SAVE_BUTTON_ID 4

#define TREE_ID 1001
#define SOUND_WINDOW_ID 1002


// Window Procedure: Handles messages sent to the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CREATESTRUCT* createStruct = nullptr;  // Declare here to avoid jump errors
    AppData *appData = (AppData *)GetWindowLongPtr(hwnd, GWLP_USERDATA); // Retrieve the appData pointer
    switch (uMsg)
    {
        // Create window
        case WM_CREATE:

            appData = new AppData();
            appData->fileDescriptor = nullptr;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)appData);
        
            createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            
            appData->hInstance = createStruct->hInstance;

            CreateProgram(appData, hwnd);
            return 0;
        // Close window
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        // Crash
        case WM_DESTROY:
            if (appData) {
                delete appData;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, 0); // Optional but good practice
            }
            return 0;

        // Left button Down
        case WM_LBUTTONDOWN:
            return 0;

        // Event handler for file menu
        case WM_COMMAND:
            HandleCommandEvent(appData, wParam, hwnd);
            return 0;

        // Event handler for treeview
        case WM_NOTIFY:
            HandleTreeviewEvent(appData, lParam);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void AddMenus(HWND hwnd)
{
    HMENU hMenu = CreateMenu();

    HMENU hFileMenu = CreateMenu();

    AppendMenuA(hFileMenu, MF_POPUP, OPEN_FILE_MENU_ID, "Open");
    AppendMenuA(hFileMenu, MF_POPUP, CLOSE_FILE_MENU_ID, "Close");
    AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    SetMenu(hwnd, hMenu);
}

void CreateProgram(AppData *appData, HWND hwnd)
{
    AddMenus(hwnd);
}

void HandleCommandEvent(AppData *appData, WPARAM wParam, HWND hwnd)
{
    HWND hwndTreeView;
    HWND hPlayButton;
    HWND hSaveButton;
    std::shared_ptr<FileDescriptor> fd;

    std::string soundName;
    std::shared_ptr<Sound> soundPtr;

    std::string fileLocation;

    HTREEITEM hSelectedItem;
    switch (wParam)
    {
        case OPEN_FILE_MENU_ID:

            fd = FileDescriptor::getFileDescriptorFromUser();
            try {
                appData->fileDescriptor = fd;
            }
            catch (const std::exception& e) {
                std::cout << "Exception " << e.what() << std::endl;
            }
            if(appData->hInstance == NULL) {
                return;
            }
            if(appData->fileDescriptor != nullptr) {
                hwndTreeView = ConstructTreeview(appData, hwnd, appData->hInstance);
                ConstructSoundView(appData, hwnd, appData->hInstance);
            } 
            return;
        case CLOSE_FILE_MENU_ID:
            hwndTreeView = GetDlgItem(hwnd, TREE_ID);
            if(hwndTreeView != NULL) {
                DestroyWindow(hwndTreeView);
            }
            hPlayButton = GetDlgItem(hwnd, PLAY_BUTTON_ID);
            if(hPlayButton != NULL) {
                DestroyWindow(hPlayButton);
            }

            hSaveButton = GetDlgItem(hwnd, SAVE_BUTTON_ID);
            if(hSaveButton != NULL) {
                DestroyWindow(hSaveButton);
            }
            return;
        case PLAY_BUTTON_ID:
            hwndTreeView = GetDlgItem(hwnd, TREE_ID);
            if(!hwndTreeView) {
                return;
            }
            hSelectedItem = TreeView_GetSelection(hwndTreeView);
            if(!hSelectedItem) {
                return;
            }
            soundName = GetTreeViewItemName(hwndTreeView, hSelectedItem);

            for(Sound sound : appData->fileDescriptor->sounds) {
                if (sound.name == soundName) {
                    soundPtr = std::make_shared<Sound>(sound);
                    std::thread(PlayDoomSound, soundPtr).detach();
                    return;
                }
            }
            return;
        case SAVE_BUTTON_ID:            
            hwndTreeView = GetDlgItem(hwnd, TREE_ID);
            if(!hwndTreeView) {
                return;
            }
            hSelectedItem = TreeView_GetSelection(hwndTreeView);
            if(!hSelectedItem) {
                return;
            }
            soundName = GetTreeViewItemName(hwndTreeView, hSelectedItem);            
            for(Sound sound : appData->fileDescriptor->sounds) {
                if (sound.name == soundName) {
                    std::cout << "SOUND FOUND " << std::endl;  
                    
                    fileLocation = SaveFileDialog("Wav files\0*.wav\0", "wav", sound.name);
                    if(fileLocation == std::string()) {
                        std::cout << "FILE LOCATION NOT FOUND" << std::endl;
                        return;
                    }
                    std::cout << "FILE LOCATION FOUND \"" << fileLocation << "\"" << std::endl;
                    
                    soundPtr = std::make_shared<Sound>(sound);
                    std::thread(writeToWav, fileLocation, soundPtr).detach();
                    return;
                }
            }
            std::cout << "SOUND NOT FOUND " << std::endl;            
            return;
    }
}

std::string SaveFileDialog(LPCSTR lpstrFilter, LPCSTR lpstrDefExt, std::string defaultName) {
    // Buffer to receive the file path
    char filePath[MAX_PATH] = {};
    strncpy(filePath, defaultName.c_str(), MAX_PATH - 1); // Safe copy
    // Set up the OPENFILENAME structure
    OPENFILENAME windowsFileSelectionIOObject = { 0 };
    windowsFileSelectionIOObject.lStructSize = sizeof(windowsFileSelectionIOObject);
    windowsFileSelectionIOObject.hwndOwner = NULL;
    windowsFileSelectionIOObject.lpstrFile = filePath;
    windowsFileSelectionIOObject.nMaxFile = MAX_PATH;
    windowsFileSelectionIOObject.lpstrTitle = "Save sound file";  // Dialog title
    windowsFileSelectionIOObject.lpstrFilter = lpstrFilter;
    windowsFileSelectionIOObject.lpstrDefExt = lpstrDefExt;           // Default extension
    windowsFileSelectionIOObject.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;  // Prompt if file exists

    if (GetSaveFileName(&windowsFileSelectionIOObject)) {
        return std::string(filePath);
    } else {
        return std::string();
    }
}

bool PlayDoomSound(std::shared_ptr<Sound> sound) { 
    // PlayDoomSound uses memory directly; SND_SYNC blocks until done
    BOOL success = PlaySoundA(reinterpret_cast<const char*>(soundToWav(*sound).get()), nullptr, SND_MEMORY | SND_SYNC | SND_NODEFAULT);

    return success == TRUE;
}

void HandleTreeviewEvent(AppData *appData, LPARAM lParam)
{
    // If it is the main tree
    if (((LPNMHDR)lParam)->idFrom == TREE_ID)
    {
        // lparam is a treeview, act upon it
        LPNMTREEVIEW pnmTreeView = (LPNMTREEVIEW)lParam;

        HWND hTreeView = pnmTreeView->hdr.hwndFrom;
        HTREEITEM hItem = pnmTreeView->itemNew.hItem;

        // What happened with the treeview?
        switch (pnmTreeView->hdr.code)
        {
            // Handle selection change
            case TVN_SELCHANGED:
                std::cout << "TREEVIEW ITEM \"" << GetTreeViewItemName(hTreeView, hItem) << "\" OF DEPTH [" << GetTreeViewItemDepth(hTreeView, hItem) << "] SELECTED" << std::endl;
                return;
            // Handle item expanding
            case TVN_ITEMEXPANDING:
                return;
        }
    }
}

bool RegisterWindowsClass(LPCSTR CLASS_NAME, HINSTANCE hInstance)
{
    // Define a window class (settings for the window)
    WNDCLASSEXA wc = {0};            // Properly zero-out the struct to avoid uninitialized fields
    wc.cbSize = sizeof(WNDCLASSEXA); // Required to specify the size of the struct
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = WindowProc;              // The function to be called to process the window events
    wc.hInstance = hInstance;                 // Instance of the window
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Default cursor, nothing fancy
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);

    // Register the class
    if (!RegisterClassExA(&wc))
    {
        // If registration fails, use GetLastError to debug the issue
        DWORD dwError = GetLastError();
        std::cout << "[CLASS REGISTER ERROR #" << dwError << "]" << std::endl;
        // Handle the error or log it (for debugging purposes)
        return false; // Or some other error handling
    }
    return true;
}

HWND ConstructTreeview(AppData *appData, HWND hwnd, HINSTANCE hInstance)
{
    HWND hwndTreeView = GetDlgItem(hwnd, TREE_ID);
    if(hwndTreeView == NULL) {
        hwndTreeView = CreateWindowEx(
            0, WC_TREEVIEW, TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_LINESATROOT | TVS_HASBUTTONS,
            10, 10, 300, 400,
            hwnd, (HMENU)TREE_ID, hInstance, nullptr);
    }
    else {
        TreeView_DeleteAllItems(hwndTreeView);
    }
    
    TVINSERTSTRUCT tvis;
    tvis.hParent = TVI_ROOT;      // Root of the tree
    tvis.hInsertAfter = TVI_LAST; // Insert at the end
    tvis.item.mask = TVIF_TEXT;   // We're inserting text

    // Add root item
    tvis.item.pszText = TEXT((LPSTR) const_cast<LPSTR>(appData->fileDescriptor->wadHeader->header.c_str())); 

    HTREEITEM hRoot = TreeView_InsertItem(hwndTreeView, &tvis);


    // Add a child item
    tvis.hParent = hRoot;
    tvis.item.pszText = TEXT((LPSTR) "Sounds");
    HTREEITEM hSounds = TreeView_InsertItem(hwndTreeView, &tvis);


    // Add another child item
    tvis.item.pszText = TEXT((LPSTR) "Title Pic");
    TreeView_InsertItem(hwndTreeView, &tvis);


    for(Sound sound : appData->fileDescriptor->sounds) {
        tvis.hParent = hSounds;
        tvis.item.pszText = TEXT((LPSTR) const_cast<LPSTR>(sound.name.c_str()));
        TreeView_InsertItem(hwndTreeView, &tvis);
    }


    return hwndTreeView;
}

void ConstructSoundView(AppData *appData, HWND hwnd, HINSTANCE hInstance){
    HWND hSaveButton = GetDlgItem(hwnd, SAVE_BUTTON_ID);
    if(hSaveButton == NULL) {
        hSaveButton = CreateWindowA("BUTTON", "Save",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            920, 20, 80, 30, hwnd, (HMENU)SAVE_BUTTON_ID, NULL, NULL);
    }
    HWND hPlayButton = GetDlgItem(hwnd, PLAY_BUTTON_ID);
    if(hPlayButton == NULL) {
        hPlayButton = CreateWindowA("BUTTON", "Play",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1020, 20, 80, 30, hwnd, (HMENU)PLAY_BUTTON_ID, NULL, NULL);
    }
}

void SetConsoleUp()
{
    // Allocating a new console for the application
    AllocConsole();
    // Redirect the standard output to the console
    freopen("CONOUT$", "w", stdout);
}

int GetTreeViewItemDepth(HWND hTreeView, HTREEITEM hItem)
{
    int depth = 0;
    HTREEITEM hParent = TreeView_GetParent(hTreeView, hItem);
    while (hParent)
    {
        depth++;
        hParent = TreeView_GetParent(hTreeView, hParent);
    }
    return depth;
}

std::string GetTreeViewItemName(HWND hTreeView, HTREEITEM hSelected)
{
    char szText[256];
    TVITEM tvi = { 0 };
    tvi.mask = TVIF_TEXT;
    tvi.hItem = hSelected;
    tvi.pszText = szText;
    tvi.cchTextMax = 256;

    TreeView_GetItem(hTreeView, &tvi);
    
    return std::string(szText); // Return an empty string if conversion fails
}