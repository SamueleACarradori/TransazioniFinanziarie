cmake_minimum_required(VERSION 4.1)
project(TransazioniFinanziarie)

set(CMAKE_CXX_STANDARD 20)

# Check if submodules are already initialized
set(SUBMODULE_CHECK_FILE "${CMAKE_CURRENT_SOURCE_DIR}/test/lib/googletest/googletest")

# Fetch submodules automatically
find_package(Git QUIET)
if(GIT_FOUND AND NOT EXISTS SUBMODULE_CHECK_FILE)
    execute_process(
            COMMAND git submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
    )
    execute_process(
            COMMAND git restore test/lib/googletest --recurse-submodules
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT2
    )
    if(NOT GIT_SUBMOD_RESULT EQUAL "0" OR NOT GIT_SUBMOD_RESULT2 EQUAL "0")
        message(WARNING "Git submodule update failed")
    endif()
endif()

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
