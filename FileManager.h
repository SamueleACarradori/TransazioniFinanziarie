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
 *
 * This class was initially taught as an Interface class so that every object
 * could save or delete himself inside the file, but since this solution could very
 * possibly lead to a leaks, resources mismanagement, ghost saves/deletes.
 *
 * It's been restructured as a stand-alone class that handles 1 file at a time
 * and permits manipulate it via another Interface IFileConfig
 *
**/

class FileManager {
public:
    // you can specify a path but its not recommended
    explicit FileManager(std::string fileName, std::string filePath = "");

    //check if files exists using ifstream
    static bool fileExists(const std::string& filePath);

    //save an object implementing IFileConfig interface
    bool save(const IFileConfig& obj) const;

    //load form file the object implementing IFileConfig interface
    //with the correspondent identifier
    bool load(IFileConfig& obj, const std::string& identifier) const;

    //delete line from file
    //with the correspondent identifier
    bool deleteLine(const std::string& identifier) const;

    //delete line from file
    //with the correspondent obj
    bool deleteLine(const IFileConfig& obj) const;

    //completely delete file
    bool deleteFile() const;


protected:

    //get working directory and standardize the path where to save
    static std::string getAbsolutePath(bool doStandardPath = true);

    //checks if string ends with specific suffix
    static bool endsWith(const std::string& str, const std::string& suffix);

    //verify if obj is already saved inside the file
    bool isSaved(const IFileConfig& obj) const;


private:
    std::string fileName;
    std::string filePath;
};


#endif //TRANSAZIONIFINANZIARIE_FILEMANAGER_H