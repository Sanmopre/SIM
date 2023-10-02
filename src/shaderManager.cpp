#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "shaderManager.h"

const char* readFileContent(const char* filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return nullptr;
    }

    std::string fileContent; // To store the file content

    // Read the content of the file into a string
    std::string line;
    while (std::getline(file, line)) {
        fileContent += line + "\n"; // Add newline to maintain line breaks
    }

    file.close(); // Close the file

    // Convert the string to a const char*
    const char* fileContentCStr = fileContent.c_str();

    // Allocate memory for a copy of the content to ensure it remains valid after
    // the function scope, and return the pointer to that copy
    char* contentCopy = new char[fileContent.size() + 1];
    strcpy(contentCopy, fileContentCStr);

    return contentCopy;
}