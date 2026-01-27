//
// Created by samuele on 1/25/26.
//

#ifndef TRANSAZIONIFINANZIARIE_IFILECONFIG_H
#define TRANSAZIONIFINANZIARIE_IFILECONFIG_H
#include <ostream>
#include <string>

class IFileConfig {
public:
    // Provide default implementation
    virtual ~IFileConfig() = default;

    // Standardized string for saving on file
    virtual std::string toString() const = 0;

    // The identifier is the string used to match the line we want to load
    // usually is the id
    virtual bool loadFromFile(const std::string& line, const std::string& identifier) = 0;

};
#endif //TRANSAZIONIFINANZIARIE_IFILECONFIG_H