//
// Created by samuele on 1/16/26.
//

#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <utility>



FileManager::FileManager(std::string filePath, std::string fileName) : filePath(std::move(filePath)), fileName(std::move(fileName)) {
    //TODO controls
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
    const int result = std::remove((filePath+fileName).c_str());

    if (result == 0) {
        return true;
    }
    return false;
}

bool FileManager::endsWith(const std::string &str, const std::string &suffix) {
    if (suffix.size() > str.size())
        return false;
    return str.substr(str.size() - suffix.size()) == suffix;
}
