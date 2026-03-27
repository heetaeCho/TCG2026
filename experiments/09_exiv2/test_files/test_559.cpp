#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;



class FileIoTest : public ::testing::Test {

protected:

    std::string testPath = "testfile";

    FileIo fileIo{testPath};

};



TEST_F(FileIoTest_559, OpenDefaultMode_559) {

    EXPECT_EQ(fileIo.open(), 0);

}



TEST_F(FileIoTest_559, OpenWithMode_559) {

    EXPECT_EQ(fileIo.open("rb"), 0);

}



TEST_F(FileIoTest_559, CloseFile_559) {

    fileIo.open();

    EXPECT_EQ(fileIo.close(), 0);

}



TEST_F(FileIoTest_559, SetPathAndGetPath_559) {

    std::string newPath = "newfile";

    fileIo.setPath(newPath);

    EXPECT_EQ(fileIo.path(), newPath);

}



TEST_F(FileIoTest_559, CheckIsOpenAfterOpenAndClose_559) {

    EXPECT_FALSE(fileIo.isopen());

    fileIo.open();

    EXPECT_TRUE(fileIo.isopen());

    fileIo.close();

    EXPECT_FALSE(fileIo.isopen());

}



TEST_F(FileIoTest_559, ErrorHandlingOnOpenFailure_559) {

    // Assuming open returns non-zero on failure

    FileIo invalidFile("invalidpath");

    EXPECT_NE(invalidFile.open(), 0);

}
