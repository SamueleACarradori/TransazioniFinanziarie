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
    explicit FileManager(std::string fileName, std::string filePath = "");

    static bool fileExists(const std::string& filePath);

    [[nodiscard]] bool fileExists() const;

    [[nodiscard]] bool deleteFile() const;

    [[nodiscard]] bool save(const IFileConfig& obj) const;

    [[nodiscard]] bool load(IFileConfig& obj, const std::string& identifier) const;

    [[nodiscard]] bool deleteLine(const std::string& identifier) const;


protected:

    static std::string getAbsolutePath(bool standardPath = true);

    static bool endsWith(const std::string& str, const std::string& suffix);


private:
    std::string fileName;
    std::string filePath;
};


#endif //TRANSAZIONIFINANZIARIE_FILEMANAGER_H