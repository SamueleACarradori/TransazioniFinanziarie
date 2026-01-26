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

    // Core methods
    virtual std::string toString() const = 0;

    virtual bool loadFromFile(const std::string& line) const = 0;

};
#endif //TRANSAZIONIFINANZIARIE_IFILECONFIG_H