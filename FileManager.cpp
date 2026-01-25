//
// Created by samuele on 1/16/26.
//

#include "FileManager.h"

#include <fstream>
#include <utility>



FileManager::FileManager(std::string  fileName) : fileName(std::move(fileName)) {
    //TODO
    filePath = "";
}

FileManager::FileManager(std::string filePath, std::string fileName) : filePath(std::move(filePath)), fileName(std::move(fileName)) {
}

bool FileManager::fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.is_open();
}

bool FileManager::fileExists() const{
    return fileExists(fileName);
}

bool FileManager::deleteFile() const{
}

std::string FileManager::getLine() {
}

std::string FileManager::getLine(int line) {
}
