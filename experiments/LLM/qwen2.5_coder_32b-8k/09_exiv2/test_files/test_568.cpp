#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include <string>



using namespace Exiv2;



class FileIoTest_568 : public ::testing::Test {

protected:

    std::unique_ptr<FileIo> fileIo;

    

    void SetUp() override {

        fileIo = std::make_unique<FileIo>("test_path");

    }

};



TEST_F(FileIoTest_568, PathReturnsCorrectValue_568) {

    EXPECT_EQ(fileIo->path(), "test_path");

}



TEST_F(FileIoTest_568, OpenWithoutModeReturnsZero_568) {

    EXPECT_EQ(fileIo->open(), 0);

}



TEST_F(FileIoTest_568, OpenWithModeReturnsZero_568) {

    EXPECT_EQ(fileIo->open("r"), 0);

}



TEST_F(FileIoTest_568, CloseReturnsZero_568) {

    fileIo->open();

    EXPECT_EQ(fileIo->close(), 0);

}



TEST_F(FileIoTest_568, IsOpenInitiallyFalse_568) {

    EXPECT_FALSE(fileIo->isopen());

}



TEST_F(FileIoTest_568, IsOpenTrueAfterOpen_568) {

    fileIo->open();

    EXPECT_TRUE(fileIo->isopen());

}



TEST_F(FileIoTest_568, ErrorInitiallyZero_568) {

    EXPECT_EQ(fileIo->error(), 0);

}



TEST_F(FileIoTest_568, EofInitiallyFalse_568) {

    EXPECT_FALSE(fileIo->eof());

}



TEST_F(FileIoTest_568, TellInitiallyZero_568) {

    EXPECT_EQ(fileIo->tell(), 0);

}



TEST_F(FileIoTest_568, SizeInitiallyZero_568) {

    EXPECT_EQ(fileIo->size(), 0);

}
