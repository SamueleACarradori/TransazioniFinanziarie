//
// Created by samuele on 1/16/26.
//

#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <utility>



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

bool FileManager::load(IFileConfig& obj) const {
    std::ifstream file(fileName, std::ios::in);
    bool isLoaded = false;

    if (!file.is_open()) {
        std::string line;
        while (getline(file,line) && !isLoaded) {
            isLoaded = obj.loadFromFile(line);
        }
        file.close();
    }

    return isLoaded;
}

bool FileManager::endsWith(const std::string &str, const std::string &suffix) {
    if (suffix.size() > str.size())
        return false;
    return str.substr(str.size() - suffix.size()) == suffix;
}
