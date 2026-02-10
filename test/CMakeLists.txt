#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

if (EXISTS ./lib/googletest/googletest)
    add_subdirectory(./lib/googletest)
else ()
    add_subdirectory(./lib/embedded/googletest)
endif ()

set(gtest_SOURCE_DIR ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_TEST_FILES runAllTests.cpp
        UserTest.cpp
        CheckingAccountTest.cpp
        TransactionTest.cpp
        FileManagerTest.cpp
        DateTest.cpp)

add_executable(runAllTests ${SOURCE_TEST_FILES})
target_link_libraries(runAllTests  gtest gtest_main core)