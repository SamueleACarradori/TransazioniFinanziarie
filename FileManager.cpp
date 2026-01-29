//
// Created by samuele on 1/16/26.
//

#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>


FileManager::FileManager( std::string fileName) : fileName(std::move(fileName)) {
    if (!endsWith(this->fileName, ".txt")) {
        //TODO throw exception
    }
    if(!fileExists()) {
        //TODO create file
    }
}

bool FileManager::fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.is_open();
}

bool FileManager::fileExists() const{
    return fileExists(fileName);
}

bool FileManager::deleteFile() const{
    // Returns 0 on success, non-zero on error
    const int result = std::remove(fileName.c_str());

    if (result == 0) {
        return true;
    }
    return false;
}

bool FileManager::save(const IFileConfig& obj) const {
    //open file in append
    std::ofstream file(fileName, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        file << obj.toString() << std::endl;
        file.close();
        return true;
    }
    return false;
}

bool FileManager::load(IFileConfig& obj,const std::string& identifier) const {
    std::ifstream file(fileName, std::ios::in);
    bool isLoaded = false;

    if (!file.is_open()) {
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
    std::ifstream inFile(fileName);
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
    std::ofstream outFile(fileName);
    if (outFile.is_open() && found) {
        for (const auto& l : lines) {
            outFile << l << std::endl;
        }
        outFile.close();
        return true;
    }

    return false;
}

bool FileManager::endsWith(const std::string &str, const std::string &suffix) {
    if (suffix.size() > str.size())
        return false;
    return str.substr(str.size() - suffix.size()) == suffix;
}
