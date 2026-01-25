//
// Created by samuele on 1/16/26.
//

#ifndef TRANSAZIONIFINANZIARIE_FILEMANAGER_H
#define TRANSAZIONIFINANZIARIE_FILEMANAGER_H
#include <string>

/**
 * General purpose class for handling of '.txt' files.
 * 'filePath' contains the path of the folder we want to save the file.
 * 'fileName' contains the name + '.txt' of the file we want to save the file.
**/

class FileManager {
public:
    explicit FileManager(std::string  fileName);
    FileManager(std::string filePath, std::string fileName);

    static bool fileExists(const std::string& fileName);
    bool fileExists() const;
    bool deleteFile() const;
    bool save();
    bool load();

protected:
    std::ostream openFile();


private:
    std::string filePath;
    std::string fileName;
};


#endif //TRANSAZIONIFINANZIARIE_FILEMANAGER_H