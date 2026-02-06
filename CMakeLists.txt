cmake_minimum_required(VERSION 4.1)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(test)

set(SOURCE_FILES main.cpp
        User.cpp
        User.h
        CheckingAccount.cpp
        CheckingAccount.h
        Transaction.cpp
        Transaction.h
        FileManager.cpp
        FileManager.h
        Date.cpp
        Date.h
        IFileConfig.h
        exceptions/account_dont_exists_error.h
        exceptions/account_already_exists_error.h)

add_executable(TransazioniFinanziarie main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(TransazioniFinanziarie core)
