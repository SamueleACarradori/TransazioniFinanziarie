//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_FILEMANAGER_H
#define TRANSAZIONIFINANZIARIE_FILEMANAGER_H
#include <string>

#include "IFileConfig.h"

/**
 * General purpose class for handling of '.txt' files.
 * 'filePath' contains the path of the folder we want to save the file.
 * 'fileName' contains the name + '.txt' of the file we want to save the file.
**/

class FileManager {
public:
    FileManager(std::string filePath, std::string fileName);

    static bool fileExists(const std::string& fileName);

    bool fileExists() const;

    bool deleteFile() const;

    bool save(const IFileConfig& obj) const;

    bool load(const IFileConfig& obj) const;

protected:
    static bool endsWith(const std::string& str, const std::string& suffix);


private:
    std::string filePath;
    std::string fileName;
};


#endif //TRANSAZIONIFINANZIARIE_FILEMANAGER_H