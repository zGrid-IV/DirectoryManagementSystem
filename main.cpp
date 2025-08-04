#include <iostream>      // For standard input/output (cin, cout)
#include <direct.h>      // For directory manipulation (_mkdir, _chdir, _getcwd)
#include <windows.h>     // For file listing (FindFirstFile, FindNextFile)
#include <string>        // For using std::string
#include <limits>        // For clearing input buffer

using namespace std;

/*-----------------------------------------------------------
    Utility Functions
-----------------------------------------------------------*/

// Clears any leftover or invalid input to avoid stream issues
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Gets a single-digit integer within a valid range [min–max]
int getSingleDigitInt(int min, int max) {
    string input;
    while (true) {
        cout << "Enter a number (" << min << " to " << max << "): ";
        getline(cin, input);
        if (input.length() == 1 && isdigit(input[0])) {
            int value = input[0] - '0';
            if (value >= min && value <= max)
                return value;
        }
        cout << "Invalid input. Please enter a single digit between " << min << " and " << max << ".\n";
    }
}

// Validates folder names against illegal Windows characters
bool isValidName(const string& name) {
    const string invalidChars = "\\/:*?\"<>|";
    return !name.empty() && name.find_first_of(invalidChars) == string::npos;
}

// Returns the current working directory as a string
string getCurrentDirectory() {
    char path[256];
    _getcwd(path, sizeof(path));
    return string(path);
}

/*-----------------------------------------------------------
    File Listing Functions
-----------------------------------------------------------*/

// Lists all files in the current directory
void listAllFiles() {
    WIN32_FIND_DATA file;
    HANDLE handle = FindFirstFile("*", &file);
    bool found = false;

    cout << "\n--- Files in Current Directory ---\n";

    if (handle != INVALID_HANDLE_VALUE) {
        do {
            string name = file.cFileName;
            if (name != "." && name != "..") {
                cout << " - " << name << endl;
                found = true;
            }
        } while (FindNextFile(handle, &file));
        FindClose(handle);
    }

    if (!found)
        cout << "No files found.\n";
}

// Lists files by user-specified extension (e.g. .txt)
void listByExtension() {
    string ext;
    cout << "Enter extension (e.g., .txt): ";
    getline(cin, ext);

    WIN32_FIND_DATA file;
    HANDLE handle = FindFirstFile(("*" + ext).c_str(), &file);
    bool found = false;

    if (handle != INVALID_HANDLE_VALUE) {
        cout << "\n--- Matching Files ---\n";
        do {
            cout << " - " << file.cFileName << endl;
            found = true;
        } while (FindNextFile(handle, &file));
        FindClose(handle);
    }

    if (!found)
        cout << "No files match this extension.\n";
}

// Lists files using custom pattern (e.g., data*.*)
void listByPattern() {
    string pattern;
    cout << "Enter pattern (e.g., data*.*): ";
    getline(cin, pattern);

    WIN32_FIND_DATA file;
    HANDLE handle = FindFirstFile(pattern.c_str(), &file);
    bool found = false;

    if (handle != INVALID_HANDLE_VALUE) {
        cout << "\n--- Matching Files ---\n";
        do {
            cout << " - " << file.cFileName << endl;
            found = true;
        } while (FindNextFile(handle, &file));
        FindClose(handle);
    }

    if (!found)
        cout << "No files matched your pattern.\n";
}

/*-----------------------------------------------------------
    Directory Actions
-----------------------------------------------------------*/

// Creates a new folder after validating the name
void createDirectory() {
    string folderName;
    cout << "Enter new folder name: ";
    getline(cin, folderName);

    if (!isValidName(folderName)) {
        cout << "Invalid folder name. Avoid characters like \\ / : * ? \" < > |\n";
        return;
    }

    if (_mkdir(folderName.c_str()) == 0)
        cout << "Folder created successfully.\n";
    else
        cout << "Error: Folder already exists or cannot be created.\n";
}

// Changes directory based on user's selection
void changeDirectory() {
    cout << "\n=== Change Directory ===\n";
    cout << "[1] Parent Directory\n";
    cout << "[2] Root Directory\n";
    cout << "[3] Custom Path\n";
    int choice = getSingleDigitInt(1, 3);

    char cwd[256];
    string path;

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
            getline(cin, path);
            if (_chdir(path.c_str()) == 0) {
                _getcwd(cwd, sizeof(cwd));
                cout << "Changed to: " << cwd << "\n";
            } else {
                cout << "Error: Invalid or inaccessible path.\n";
            }
            break;
    }
}

/*-----------------------------------------------------------
    Menus
-----------------------------------------------------------*/

// Displays options for file listing
void listFilesMenu() {
    cout << "\n=== File Listing Menu ===\n";
    cout << "[1] All Files\n";
    cout << "[2] By Extension\n";
    cout << "[3] By Pattern\n";
    
    int choice = getSingleDigitInt(1, 3);

    switch (choice) {
        case 1: listAllFiles(); break;
        case 2: listByExtension(); break;
        case 3: listByPattern(); break;
    }
}

// Main interactive loop of the program
void mainMenu() {
    while (true) {
        cout << "\n=== Directory Management System ===\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory/Folder\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit Program\n";

        int choice = getSingleDigitInt(1, 4);

        switch (choice) {
            case 1: listFilesMenu(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4:
                cout << "Goodbye! Thanks for using the system.\n";
                return;
        }
    }
}

/*-----------------------------------------------------------
    Entry Point
-----------------------------------------------------------*/

int main() {
    mainMenu();  // Starts the interactive session
    return 0;
}
