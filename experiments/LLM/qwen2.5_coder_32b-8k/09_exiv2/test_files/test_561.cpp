#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Eq;



class FileIoTest_561 : public ::testing::Test {

protected:

    std::string testFilePath = "testfile.txt";

    FileIo fileIo;



    FileIoTest_561() : fileIo(testFilePath) {}

};



TEST_F(FileIoTest_561, IsOpenInitiallyFalse_561) {

    EXPECT_FALSE(fileIo.isopen());

}



TEST_F(FileIoTest_561, OpenWithoutModeSucceeds_561) {

    EXPECT_EQ(0, fileIo.open());

    EXPECT_TRUE(fileIo.isopen());

    fileIo.close();

}



TEST_F(FileIoTest_561, OpenWithModeSucceeds_561) {

    EXPECT_EQ(0, fileIo.open("r"));

    EXPECT_TRUE(fileIo.isopen());

    fileIo.close();

}



TEST_F(FileIoTest_561, CloseAfterOpenSucceeds_561) {

    fileIo.open();

    EXPECT_EQ(0, fileIo.close());

    EXPECT_FALSE(fileIo.isopen());

}



TEST_F(FileIoTest_561, OpenFailsWithInvalidMode_561) {

    EXPECT_NE(0, fileIo.open("invalid_mode"));

    EXPECT_FALSE(fileIo.isopen());

}



TEST_F(FileIoTest_561, ReOpenAfterCloseSucceeds_561) {

    fileIo.open();

    fileIo.close();

    EXPECT_EQ(0, fileIo.open());

    EXPECT_TRUE(fileIo.isopen());

}



TEST_F(FileIoTest_561, IsOpenReturnsFalseAfterClose_561) {

    fileIo.open();

    fileIo.close();

    EXPECT_FALSE(fileIo.isopen());

}
