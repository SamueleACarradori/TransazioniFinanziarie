cmake_minimum_required(VERSION 4.1)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

add_executable(TransazioniFinanziarie main.cpp
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
        test/runAllTests.cpp)
