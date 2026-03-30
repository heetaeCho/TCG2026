#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class FileIoTest : public ::testing::Test {

protected:

    void SetUp() override {

        fileIo = std::make_unique<FileIo>("test_file.txt");

    }



    void TearDown() override {

        fileIo.reset();

    }



    std::unique_ptr<FileIo> fileIo;

};



TEST_F(FileIoTest_560, OpenWithValidMode_ReturnsZero_560) {

    EXPECT_EQ(fileIo->open("r"), 0);

}



TEST_F(FileIoTest_560, OpenWithInvalidMode_ReturnsOne_560) {

    EXPECT_EQ(fileIo->open("invalid_mode"), 1);

}



TEST_F(FileIoTest_560, OpenMultipleTimes_CloseBeforeOpen_ReturnsZero_560) {

    fileIo->open("r");

    fileIo->close();

    EXPECT_EQ(fileIo->open("w"), 0);

}



TEST_F(FileIoTest_560, OpenAlreadyOpenedFile_ReturnsZero_560) {

    fileIo->open("r");

    EXPECT_EQ(fileIo->open("r"), 0);

}



TEST_F(FileIoTest_560, CloseUnopenedFile_DoesNotThrow_560) {

    EXPECT_NO_THROW(fileIo->close());

}



TEST_F(FileIoTest_560, OpenWithEmptyMode_ReturnsOne_560) {

    EXPECT_EQ(fileIo->open(""), 1);

}
