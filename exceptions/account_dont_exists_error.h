//
// Created by samuele on 1/30/26.
//

#ifndef TRANSAZIONIFINANZIARIE_ACCOUNT_DONT_EXISTS_ERROR_H
#define TRANSAZIONIFINANZIARIE_ACCOUNT_DONT_EXISTS_ERROR_H

#include <exception>
#include <stdexcept>
#include <string>

class account_dont_exists_error : public std::runtime_error {
public:
    // Constructor accepting const char*
    explicit account_dont_exists_error() noexcept : runtime_error("Account does not exists."){}

    // Override what() method, marked
    // noexcept for modern C++ (means the function does not throw any exception)
    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};


#endif //TRANSAZIONIFINANZIARIE_ACCOUNT_DONT_EXISTS_ERROR_H