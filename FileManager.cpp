//
// Created by samuele on 1/16/26.
//

#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>


FileManager::FileManager( std::string fileName, std::string filePath) : fileName(std::move(fileName)), filePath(std::move(filePath)) {
    if (!endsWith(this->fileName, ".txt")) {
        throw std::invalid_argument("The name of the file must end with .txt");
    }

    if (this->filePath.empty()) {
        this->filePath = FileManager::getAbsolutePath();
        if (!endsWith(this->filePath,"/")) {
            this->filePath = this->filePath + "/";
        }
        this->filePath = this->filePath + this->fileName;
    }

    if(!fileExists()) {
        //using ofstream for output file operations.
        std::ofstream file;
        file.open(this->filePath);

        // Check if the file was successfully created.
        if (!file.is_open()){
            throw std::runtime_error("Could not create file "+fileName+".");
        }
        file.close();
    }
}

bool FileManager::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    const bool isOpen = file.is_open();
    file.close();
    return isOpen;
}

bool FileManager::fileExists() const{
    return fileExists(this->filePath);
}

bool FileManager::deleteFile() const{
    // Returns 0 on success, non-zero on error
    if ( std::remove(filePath.c_str()) == 0) {
        return true;
    }
    return false;
}

bool FileManager::save(const IFileConfig& obj) const {
    //open file in append
    std::ofstream file(filePath, std::ios::out | std::ios::app);

    if (file.is_open()) {
        file << obj.toString() << std::endl;
        file.close();
        return true;
    }
    return false;
}

bool FileManager::load(IFileConfig& obj,const std::string& identifier) const {
    std::ifstream file(filePath, std::ios::in);
    bool isLoaded = false;

    if (file.is_open()) {
        std::string line;
        while (getline(file,line) && !isLoaded) {
            if (line.find(identifier) != std::string::npos) {
                isLoaded = obj.loadFromString(line);
            }
        }
        file.close();
    }

    return isLoaded;
}

bool FileManager::deleteLine(const std::string &identifier) const {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    bool found = false;

    // Read all lines into memory
    while (std::getline(inFile, line)) {
        // if the identifier is not inside the line find() return npos
        // we want to save all the non match lines
        // when we find the line we want to delete we skip it and mark as found

        if (line.find(identifier) == std::string::npos) {
            lines.push_back(line);
        }else {
            found = true;
        }
    }
    inFile.close();

    // Write back all lines except the removed one
    std::ofstream outFile(filePath);
    if (outFile.is_open() && found) {
        for (const auto& l : lines) {
            outFile << l << std::endl;
        }
        outFile.close();
        return true;
    }

    return false;
}

std::string FileManager::getAbsolutePath(const bool standardPath) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        throw std::runtime_error("Unable to locate working directory.");
    }
    auto filePath = std::string(cwd);

    //fix cmake-build-debug removing it from the filepath
    if (standardPath) {
        if (const std::string stringToRemove = "cmake-build-debug"; endsWith(filePath, stringToRemove)) {
            const auto start_position_to_erase = filePath.find(stringToRemove);
            filePath = filePath.erase(start_position_to_erase, stringToRemove.length());
        }
        filePath = filePath + "database/";
    }
    return filePath;
}

bool FileManager::endsWith(const std::string &str, const std::string &suffix) {
    if (suffix.size() > str.size())
        return false;
    return str.substr(str.size() - suffix.size()) == suffix;
}
