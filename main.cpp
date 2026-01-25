#include <fstream>
#include <iostream>

int main() {
        //  append mode
        std::ofstream fio("abc.txt", std::ios::app);

        // Check if the file is opened successfully
        if (fio.is_open()) {

            std::cout << "File opened successfully." << std::endl;

            // Append content to the file
            fio << "This text is appended to the file." << std::endl;

            // Close the file
            fio.close();

            std::cout << "File closed." << std::endl;
        }
        else {
            // Display error if file was not opened
            std::cout << "Error opening file!" << std::endl;
        }

        return 0;
}