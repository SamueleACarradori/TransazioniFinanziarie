//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../User.h"

class FileManagerFixture : public ::testing::Test {
protected:

    User user;
    FileManager userFileManager = FileManager("USER_TEST.txt");
};

TEST_F(FileManagerFixture, ConstructorCall) {
    //OK
    ASSERT_NO_THROW(FileManager("USER_TEST2.txt"));

    // no .txt
    ASSERT_THROW(FileManager("USER_TEST3"),std::invalid_argument);

    //non existent dir
    ASSERT_THROW(FileManager("/invalid/argument.txt"),std::runtime_error);

    //non existent dir
    ASSERT_THROW(FileManager("USER_TESTING.txt","/invalid/argument"),std::runtime_error);
}

TEST_F(FileManagerFixture, SaveLoadFile) {

    //these methods may have some problems at runtime so testing here is showing that they just work properly
    // also I am using this to populate the file.
    // Made as expect_true because if the files are not deleted in the
    // DeleteFile test they will produce an error
    EXPECT_TRUE(userFileManager.save(User("TEST1","PROVAID0")));
    EXPECT_TRUE(userFileManager.save(User("TEST2","PROVAID1")));
    EXPECT_TRUE(userFileManager.save(User("TEST3","PROVAID2")));

    //Try saving already existing file
    ASSERT_FALSE(userFileManager.save(User("TEST3","PROVAID2")));

    //OK
    ASSERT_TRUE(userFileManager.load(user,"PROVAID0"));

    //not able to load user not identifiable
    ASSERT_FALSE(userFileManager.load(user,"randomid"));

}

TEST_F(FileManagerFixture, DeleteFile) {

    //OK
    ASSERT_TRUE(userFileManager.deleteLine("PROVAID0"));

    // non existent line
    ASSERT_FALSE(userFileManager.deleteLine("nonexistentid"));

    // non existent User
    ASSERT_FALSE(userFileManager.deleteLine(User("TEST1","PROVAID0")));

    //delete all the generated files
    //errors may come from std library at runtime
    ASSERT_TRUE(userFileManager.deleteFile());

    ASSERT_TRUE(FileManager("USER_TEST2.txt").deleteFile());
}

