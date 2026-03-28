#include <gtest/gtest.h>

#include "Stream.h"

#include "GooFile.h"



class MockGooFile : public GooFile {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class FileStreamTest_150 : public ::testing::Test {

protected:

    std::unique_ptr<MockGooFile> mockFile;

    std::unique_ptr<FileStream> fileStream;



    void SetUp() override {

        mockFile = std::make_unique<MockGooFile>();

        fileStream = std::make_unique<FileStream>(mockFile.get(), 0, false, 16384, Object());

    }



    void TearDown() override {

        fileStream.reset();

        mockFile.reset();

    }

};



TEST_F(FileStreamTest_150, LookChar_NormalOperation_150) {

    EXPECT_CALL(*mockFile, getChar())

        .WillOnce(testing::Return('A'));



    int result = fileStream->lookChar();

    EXPECT_EQ(result, 'A');

}



TEST_F(FileStreamTest_150, LookChar_BufferNotEmpty_150) {

    // Assuming the buffer is pre-filled with data for this test case

    fileStream->setPos(0, 0);

    int result = fileStream->lookChar();

    EXPECT_NE(result, EOF);

}



TEST_F(FileStreamTest_150, LookChar_EOF_Reached_150) {

    // Assuming the buffer is empty and fillBuf returns false

    EXPECT_CALL(*mockFile, getChar())

        .WillOnce(testing::Return(EOF));



    int result = fileStream->lookChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(FileStreamTest_150, LookChar_BoundaryCondition_EmptyBuffer_150) {

    // Assuming the buffer is empty and fillBuf returns true, then getChar returns valid data

    EXPECT_CALL(*mockFile, getChar())

        .WillOnce(testing::Return('B'));



    int result = fileStream->lookChar();

    EXPECT_EQ(result, 'B');

}



TEST_F(FileStreamTest_150, LookChar_ExceptionalCase_FileError_150) {

    // Assuming the buffer is empty and fillBuf returns false due to an error

    EXPECT_CALL(*mockFile, getChar())

        .WillOnce(testing::Return(EOF));



    int result = fileStream->lookChar();

    EXPECT_EQ(result, EOF);

}
