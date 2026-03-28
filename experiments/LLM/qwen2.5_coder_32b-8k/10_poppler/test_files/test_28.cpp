#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/ImgWriter.h"

#include <cstdio>



class MockFILE {

public:

    MOCK_METHOD3(init, bool(FILE*, int, int));

    MOCK_METHOD2(writePointers, bool(unsigned char**, int));

    MOCK_METHOD1(writeRow, bool(unsigned char**));

    MOCK_METHOD0(close, bool());

};



class ImgWriterTest_28 : public ::testing::Test {

protected:

    MockFILE mockFile;

    FILE* file = nullptr;



    void SetUp() override {

        file = fopen("testfile", "w");

        if (!file) {

            GTEST_SKIP() << "Failed to open test file.";

        }

    }



    void TearDown() override {

        if (file) {

            fclose(file);

        }

        remove("testfile");

    }

};



TEST_F(ImgWriterTest_28, InitWithValidFile_28) {

    ImgWriter writer;

    EXPECT_CALL(mockFile, init(file, 100, 100)).WillOnce(::testing::Return(true));

    bool result = writer.init(file, 100, 100);

    EXPECT_TRUE(result);

}



TEST_F(ImgWriterTest_28, InitWithInvalidFile_28) {

    ImgWriter writer;

    FILE* invalidFile = nullptr;

    EXPECT_CALL(mockFile, init(invalidFile, 100, 100)).WillOnce(::testing::Return(false));

    bool result = writer.init(invalidFile, 100, 100);

    EXPECT_FALSE(result);

}



TEST_F(ImgWriterTest_28, WritePointersWithValidData_28) {

    ImgWriter writer;

    unsigned char* rows[1] = {new unsigned char[100]};

    EXPECT_CALL(mockFile, writePointers(rows, 1)).WillOnce(::testing::Return(true));

    bool result = writer.writePointers(rows, 1);

    EXPECT_TRUE(result);

    delete[] rows[0];

}



TEST_F(ImgWriterTest_28, WriteRowWithValidData_28) {

    ImgWriter writer;

    unsigned char* row = new unsigned char[100];

    unsigned char* rowPtrs[1] = {row};

    EXPECT_CALL(mockFile, writeRow(rowPtrs)).WillOnce(::testing::Return(true));

    bool result = writer.writeRow(rowPtrs);

    EXPECT_TRUE(result);

    delete[] row;

}



TEST_F(ImgWriterTest_28, CloseSuccessfully_28) {

    ImgWriter writer;

    EXPECT_CALL(mockFile, close()).WillOnce(::testing::Return(true));

    bool result = writer.close();

    EXPECT_TRUE(result);

}



TEST_F(ImgWriterTest_28, SupportCMYKDefaultFalse_28) {

    ImgWriter writer;

    bool result = writer.supportCMYK();

    EXPECT_FALSE(result);

}
