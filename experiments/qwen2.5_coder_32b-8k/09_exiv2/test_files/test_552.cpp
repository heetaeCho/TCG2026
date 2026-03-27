#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class FileIoTest_552 : public ::testing::Test {

protected:

    std::string testFilePath = "testfile.bin";

    FileIo* fileIo;



    void SetUp() override {

        fileIo = new FileIo(testFilePath);

    }



    void TearDown() override {

        delete fileIo;

        std::remove(testFilePath.c_str());

    }

};



TEST_F(FileIoTest_552, WriteNormalOperation_552) {

    ASSERT_EQ(fileIo->open("wb"), 0);



    const byte data[] = {1, 2, 3, 4, 5};

    size_t bytesWritten = fileIo->write(data, sizeof(data));

    EXPECT_EQ(bytesWritten, sizeof(data));



    fileIo->close();

}



TEST_F(FileIoTest_552, WriteBoundaryConditionZeroBytes_552) {

    ASSERT_EQ(fileIo->open("wb"), 0);



    const byte data[] = {1, 2, 3};

    size_t bytesWritten = fileIo->write(data, 0);

    EXPECT_EQ(bytesWritten, 0);



    fileIo->close();

}



TEST_F(FileIoTest_552, WriteBoundaryConditionLargeBytes_552) {

    ASSERT_EQ(fileIo->open("wb"), 0);



    const size_t largeSize = 1024 * 1024; // 1MB

    std::vector<byte> data(largeSize, 0xFF);

    size_t bytesWritten = fileIo->write(data.data(), largeSize);

    EXPECT_EQ(bytesWritten, largeSize);



    fileIo->close();

}



TEST_F(FileIoTest_552, WriteErrorCaseFileNotOpen_552) {

    const byte data[] = {1, 2, 3};

    size_t bytesWritten = fileIo->write(data, sizeof(data));

    EXPECT_EQ(bytesWritten, 0);

}



TEST_F(FileIoTest_552, WriteErrorCaseInvalidMode_552) {

    ASSERT_EQ(fileIo->open("rb"), 0);



    const byte data[] = {1, 2, 3};

    size_t bytesWritten = fileIo->write(data, sizeof(data));

    EXPECT_EQ(bytesWritten, 0);



    fileIo->close();

}
