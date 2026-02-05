find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#add_subdirectory(./lib/googletest)
#set(gtest_SOURCE_DIR ./lib/googletest/)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES runAllTests.cpp
        UserTest.cpp
        CheckingAccountTest.cpp
        TransactionTest.cpp
        FileManagerTest.cpp
        DateTest.cpp)
add_executable(runAllTests ${SOURCE_FILES})
target_link_libraries(runAllTests ${GTEST_BOTH_LIBRARIES} core)