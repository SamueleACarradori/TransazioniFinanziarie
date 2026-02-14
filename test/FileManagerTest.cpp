//
// Created by samuele on 2/5/26.
//

#include <gtest/gtest.h>
#include "../User.h"

class FileManagerFixture : public ::testing::Test {
protected:

    void TearDown() override {
        if (!FileManager("USER_TEST2.txt").deleteFile()
            || !FileManager("USER_TEST3.txt").deleteFile())
            throw std::runtime_error("Unable to delete files in FileManager, test failed");
    }

    //for loading
    User user;

    FileManager userFileManager = FileManager("USER_TEST.txt");
};

TEST_F(FileManagerFixture, ConstructorCall) {
    //Should create correctly the file
    EXPECT_NO_THROW(FileManager("USER_TEST2.txt"));

    // no .txt at the end gets added
    EXPECT_NO_THROW(FileManager("USER_TEST3"));

    //non existent dir
    ASSERT_THROW(FileManager("/invalid/argument.txt"),std::runtime_error);

    //non existent dir
    ASSERT_THROW(FileManager("USER_TESTING.txt","/invalid/argument/"),std::runtime_error);
}

TEST_F(FileManagerFixture, SaveLoadFile) {
    // these methods may have some problems at runtime so testing here is showing that they just work properly
    // also I am using this to populate the file.

    // Made as expect_true because if the files are not deleted in the DeleteFile test they will produce an error
    EXPECT_TRUE(userFileManager.save(User("TEST1","PROVAID0")));
    EXPECT_TRUE(userFileManager.save(User("TEST2","PROVAID1")));
    EXPECT_TRUE(userFileManager.save(User("TEST3","PROVAID2")));

    //Try saving already existing file
    EXPECT_FALSE(userFileManager.save(User("TEST3","PROVAID2")));

    //Should correctly load the user since the file contains it
    EXPECT_TRUE(userFileManager.load(user,"PROVAID0"));

    //not able to load user not identifiable
    EXPECT_FALSE(userFileManager.load(user,"randomid"));

}

TEST_F(FileManagerFixture, DeleteFile) {

    //Correctly delete line containing identifier
    EXPECT_TRUE(userFileManager.deleteLine("PROVAID0"));

    // non existent line inside file
    EXPECT_FALSE(userFileManager.deleteLine("nonexistentid"));

    // non existent User inside file
    EXPECT_FALSE(userFileManager.deleteLine(User("TEST1","PROVAID0")));

    //delete the file
    //errors may come from std library at runtime :(
    EXPECT_TRUE(userFileManager.deleteFile());

    // try deleting already deleted file
    EXPECT_FALSE(userFileManager.deleteFile());
}

