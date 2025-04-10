#ifndef APPDATA_H
#define APPDATA_H

#include "FileDescriptor.h"

// Forward declaration of FileDescriptor

struct AppData {
    std::shared_ptr<FileDescriptor> fileDescriptor;
    HINSTANCE hInstance;
};

#endif // APPDATA_H