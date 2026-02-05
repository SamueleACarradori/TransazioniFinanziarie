//
// Created by samuele on 2/5/26.
//

#include <stdexcept>

class account_already_exists_error : public std::runtime_error {
public:
    // Constructor accepting const char*
    explicit account_already_exists_error() noexcept : runtime_error("Account already exists."){}

    // Override what() method, marked
    // noexcept for modern C++ (means the function does not throw any exception)
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};
