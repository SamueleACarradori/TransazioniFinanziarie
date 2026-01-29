//
// Created by samuele on 1/25/26.
//

#ifndef TRANSAZIONIFINANZIARIE_IFILECONFIG_H
#define TRANSAZIONIFINANZIARIE_IFILECONFIG_H

#include <memory>
#include <random>
#include <sstream>
#include <string>

/**
 * Interface created to give a common framework for all the classes that needs to be saved on file.
 * Althow I recognize it may be not the most efficient way  to save files on big scale project
 * it is also a somewhat 'elegant' solution to a common problem I faced while doing this project.
 */

class IFileConfig {
public:
    // Default Constructor since no attributes
    IFileConfig() = default;

    // Copy Constructor
    IFileConfig(const IFileConfig& obj) {
        // calling init() this way should automatically call
        // the function redefined inside the derived class
        // also if init() is not redefined throws an exception
        init(&obj);
    }

    // Provide destructor default implementation
    virtual ~IFileConfig() = default;

    // Standardized string for saving on file
    virtual std::string toString() const = 0;

    /*
     * NOTEtoSELF:
     * I could have made the loadFromString() methods take a char in input that
     * has the role of delimiter but after some thinking, I came to the conclusion that
     * if I am redefining in the child class the toString() method with my delimiter
     * then I should not allow other actors inside the program to possibly
     * broke the software by changing my standard implementation.
     */

    // The identifier is the string used to match the line
    // we want to load usually is the id
    //virtual bool loadFromString(const std::string& line, const std::string& identifier) = 0;

    /* Standardizing loading from file.txt
     * I thought of making this method not pure virtual, but I wanted every child class
     * to redefine it so that is visible in the .cpp the kind of implementation each one
     * of them has without having to run with runtime call backlog if something goes wrong.
     */
    virtual void loadFromString(const std::string& line) = 0;

protected:

    /*This method is protected because the scope of this class is to create a framework
     *to interface with a class that saves files on .txt
     *so we do not want anyone but the class to define the delimiter
     *this class has the purpose to solve the general problem of loading while
     *the actual call is made from the public twin method */
    virtual void loadFromString(const std::string& line, const char delimiter) {
        std::stringstream ss(line);
        std::string split;

        short i = 0;
        while (getline(ss, split, delimiter)) {
            //uses the redefined method in each child class
            init(i,split);
            i++;
        }
    }

    //Init is defined here so that all subclasses have it for Copy Constructor
    //to fix the inheritance problem the IFileConfig method just throws an exception when called
    // ensuring that the right call at runtime is made //TODO test it
    virtual void init(const IFileConfig* obj) {
        //TODO throw exception
    };

    //Initialize specific child object during loadFromString()
    virtual void init(int index, const std::string& attribute) = 0;


    // Just an overkill method for solving a basic random string gen problem
    static std::string generateRandomString(const int length = 8, const bool specialChar = false) {
        std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        if (specialChar)
            characters = characters + "!@#$%^&*-+";

        // Generating true random using entropy on the system. Could be slow and expensive so we made it static
        static std::random_device random_device;

        /*
         * Mersenne Twister pseudo-random number generator, 19937 = period length (2¹⁹⁹³⁷ - 1)
         * We seed it with a true random number to get a more pure-random-like result
         */
        std::mt19937 generator(random_device());

        // Produces random integers uniformly distributed across a range
        std::uniform_int_distribution<> distribution(0, characters.size() - 1);

        // Generating the actual string
        std::string random_string;
        random_string.reserve(length); //optimization pre allocating

        /**
         * distribution(generator) generates a random index (int type)
         * Then we select from the characters the one with the correspondent index
         * and we put it inside result string
        */
        for (size_t i = 0; i < length; ++i) {
            random_string += characters[distribution(generator)];
        }

        return random_string;
    }
};
#endif //TRANSAZIONIFINANZIARIE_IFILECONFIG_H