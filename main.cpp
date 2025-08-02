#include <iostream>
#include <direct.h>   // for _mkdir, _getcwd, _chdir
#include <windows.h>  // for FindFirstFile, FindNextFile
#include <string>

using namespace std;

void listAllFiles() {
    WIN32_FIND_DATA file;
    HANDLE searchHandle = FindFirstFile("*", &file);

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            cout << file.cFileName << endl;
        } while (FindNextFile(searchHandle, &file));
        FindClose(searchHandle);
    } else {
        cout << "No files found.\n";
    }
}

void listByExtension() {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    cin >> ext;

    WIN32_FIND_DATA file;
    HANDLE searchHandle = FindFirstFile(("*" + ext).c_str(), &file);

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            cout << file.cFileName << endl;
        } while (FindNextFile(searchHandle, &file));
        FindClose(searchHandle);
    } else {
        cout << "No matching files found.\n";
    }
}

void listByPattern() {
    string pattern;
    cout << "Enter pattern (e.g., moha*.*): ";
    cin >> pattern;

    WIN32_FIND_DATA file;
    HANDLE searchHandle = FindFirstFile(pattern.c_str(), &file);

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            cout << file.cFileName << endl;
        } while (FindNextFile(searchHandle, &file));
        FindClose(searchHandle);
    } else {
        cout << "No files matched the pattern.\n";
    }
}

void listFilesMenu() {
    int choice;
    cout << "\n[1] List All Files\n[2] List by Extension\n[3] List by Pattern\nEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: listAllFiles(); break;
        case 2: listByExtension(); break;
        case 3: listByPattern(); break;
        default: cout << "Invalid choice.\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter directory name: ";
    cin >> dirName;

    if (_mkdir(dirName.c_str()) == 0) {
        cout << "Directory created successfully.\n";
    } else {
        cout << "Error: Directory may already exist or cannot be created.\n";
    }
}

void changeDirectory() {
    int choice;
    string path;
    char cwd[256];

    cout << "\n=== Change Directory ===\n";
    cout << "[1] Move to Parent Directory\n[2] Move to Root Directory\n[3] Enter Custom Path\nSelect an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            if (_chdir("..") == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Moved to parent directory: " << cwd << "\n";
            } else {
                cout << "Error: Unable to move to parent directory.\n";
            }
            break;
        case 2:
            if (_chdir("C:\\") == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Moved to root directory: " << cwd << "\n";
            } else {
                cout << "Error: Unable to move to root directory.\n";
            }
            break;
        case 3:
            cout << "Enter full path to directory: ";
            cin.ignore(); // Clear newline left in buffer
            getline(cin, path);
            if (_chdir(path.c_str()) == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Changed to: " << cwd << "\n";
            } else {
                cout << "Error: Invalid or inaccessible path.\n";
            }
            break;
        default:
            cout << "Invalid option.\n";
    }
}

void mainMenu() {
    int option;
    do {
        cout << "\n=== Directory Management System ===\n";
        cout << "[1] List Files\n[2] Create Directory\n[3] Change Directory\n[4] Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1: listFilesMenu(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);
}

int main() {
    mainMenu();
    return 0;
}


