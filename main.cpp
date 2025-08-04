
#include <iostream>      // For cout and cin
#include <direct.h>      // For directory functions: _mkdir, _getcwd, _chdir
#include <windows.h>     // For file listing: FindFirstFile, FindNextFile
#include <string>        // For handling user input strings

using namespace std;

// Shows all files in the current directory
void listAllFiles() {
    WIN32_FIND_DATA file;
    HANDLE searchHandle = FindFirstFile("*", &file);  // * means all files

    bool filesFound = false;

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            const char* name = file.cFileName;
            if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
                cout << name << endl;
                filesFound = true;
            }
        } while (FindNextFile(searchHandle, &file));

        FindClose(searchHandle);
    }

    if (!filesFound) {
        cout << "No files found in the current directory.\n";
    }
}


// Shows files that match a specific extension (like .txt)
void listByExtension() {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    cin >> ext;

    WIN32_FIND_DATA file;
    HANDLE searchHandle = FindFirstFile(("*" + ext).c_str(), &file);  // Search for *.ext

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            cout << file.cFileName << endl;
        } while (FindNextFile(searchHandle, &file));
        FindClose(searchHandle);
    } else {
        cout << "No matching files found.\n";
    }
}

// Shows files that match a custom pattern
void listByPattern() {
    string pattern;
    cout << "Enter pattern (e.g., data*.*): ";
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

// File listing menu where user chooses how to view files
void listFilesMenu() {
    string input;
    int choice;

    cout << "\n[1] List All Files\n[2] List by Extension\n[3] List by Pattern\nEnter choice (1 to 3): ";
    cin >> input;

    if (input.length() != 1 || !isdigit(input[0])) {
        cout << "Invalid input. Please enter a single digit from 1 to 3.\n";
        return;
    }

    choice = input[0] - '0';

    switch (choice) {
        case 1: listAllFiles(); break;
        case 2: listByExtension(); break;
        case 3: listByPattern(); break;
        default: cout << "Invalid input. Please enter a digit from 1 to 3.\n"; break;
    }
}


// Creates a new directory
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

// Lets user move between folders
void changeDirectory() {
    int choice;
    string path;
    char cwd[256];  // Will store current working directory

    cout << "\n=== Change Directory ===\n";
    cout << "[1] Move to Parent Directory\n[2] Move to Root Directory\n[3] Enter Custom Path\nSelect an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            if (_chdir("..") == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Moved to parent directory: " << cwd << "\n";
            } else {
                cout << "Error: Unable to move.\n";
            }
            break;
        case 2:
            if (_chdir("C:\\") == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Moved to root directory: " << cwd << "\n";
            } else {
                cout << "Error: Unable to move.\n";
            }
            break;
        case 3:
            cout << "Enter full path: ";
            cin.ignore(); // To handle leftover newline
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

// Main menu for the whole program
void mainMenu() {
    string input;
    int option;

    do {
        cout << "\n=== Directory Management System ===\n";
        cout << "[1] List Files\n[2] Create Directory\n[3] Change Directory\n[4] Exit\n";
        cout << "Select an option (1 to 4): ";
        cin >> input;

        // Check if input is exactly 1 character and is a digit from '1' to '4'
        if (input.length() != 1 || !isdigit(input[0])) {
            cout << "Invalid input. Please enter a single digit from 1 to 4.\n";
            continue;
        }

        option = input[0] - '0';

        switch (option) {
            case 1: listFilesMenu(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting program...\n"; break;
            default: cout << "Invalid input. Please enter a digit from 1 to 4.\n"; break;
        }
    } while (option != 4);
}



// Starting point of the program
int main() {
    mainMenu();  // Run the menu loop
    return 0;
}
