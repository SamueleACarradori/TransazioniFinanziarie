//
// Created by samuele on 1/25/26.
//

#ifndef TRANSAZIONIFINANZIARIE_IFILECONFIG_H
#define TRANSAZIONIFINANZIARIE_IFILECONFIG_H

#include "FileManager.h"
#include <string>

/**
 * Interface created to give a common framework for all the classes that needs to be saved on file.
 * Althow I recognize it may be not the most efficient way  to save files on big scale project
 * it is also a somewhat 'elegant' solution to a common problem I faced while doing this project.
 */

class IFileConfig {
public:
    // Default Constructor
    IFileConfig() = default;

    // Copy Constructor
    IFileConfig(IFileConfig& obj) {
        // calling init() this way should automatically call
        // the function redefined inside the derived class
        // also if init() is not redefined throws an exception
        init();
    }

    // Provide destructor default implementation
    virtual ~IFileConfig() = default;

    // Standardized string for saving on file
    virtual std::string toString() const = 0;

    // The identifier is the string used to match the line
    // we want to load usually is the id
    virtual bool loadFromString(const std::string& line, const std::string& identifier) = 0;

protected:
    virtual void init() {
        //TODO throw exception
    };
};
#endif //TRANSAZIONIFINANZIARIE_IFILECONFIG_H