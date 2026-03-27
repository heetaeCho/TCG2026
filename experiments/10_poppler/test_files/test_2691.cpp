#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>



extern "C" {

    cairo_status_t writeStream(void *closure, const unsigned char *data, unsigned int length);

}



class WriteStreamTest : public ::testing::Test {

protected:

    FILE* file;

    unsigned char testData[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10};



    void SetUp() override {

        file = tmpfile();

        if (!file) {

            FAIL() << "Failed to create temporary file.";

        }

    }



    void TearDown() override {

        if (file) {

            fclose(file);

        }

    }

};



TEST_F(WriteStreamTest_2691, NormalOperation_2691) {

    unsigned int length = sizeof(testData);

    cairo_status_t status = writeStream(file, testData, length);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);



    // Rewind and check if data is written correctly

    rewind(file);

    unsigned char readData[10];

    size_t bytesRead = fread(readData, 1, sizeof(readData), file);

    EXPECT_EQ(bytesRead, length);

    EXPECT_EQ(memcmp(testData, readData, length), 0);

}



TEST_F(WriteStreamTest_2691, ZeroLength_2691) {

    unsigned int length = 0;

    cairo_status_t status = writeStream(file, testData, length);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);



    // Rewind and check if no data is written

    rewind(file);

    unsigned char readData[1];

    size_t bytesRead = fread(readData, 1, sizeof(readData), file);

    EXPECT_EQ(bytesRead, 0);

}



TEST_F(WriteStreamTest_2691, LargeLength_2691) {

    unsigned int largeLength = 1024 * 1024; // 1MB

    unsigned char* largeTestData = new unsigned char[largeLength];

    memset(largeTestData, 0xFF, largeLength);



    cairo_status_t status = writeStream(file, largeTestData, largeLength);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);



    // Rewind and check if data is written correctly

    rewind(file);

    unsigned char readData[1024 * 1024];

    size_t bytesRead = fread(readData, 1, sizeof(readData), file);

    EXPECT_EQ(bytesRead, largeLength);

    EXPECT_EQ(memcmp(largeTestData, readData, largeLength), 0);



    delete[] largeTestData;

}



TEST_F(WriteStreamTest_2691, NullData_2691) {

    unsigned int length = sizeof(testData);

    cairo_status_t status = writeStream(file, nullptr, length);

    EXPECT_EQ(status, CAIRO_STATUS_WRITE_ERROR);

}



TEST_F(WriteStreamTest_2691, NullFile_2691) {

    unsigned int length = sizeof(testData);

    cairo_status_t status = writeStream(nullptr, testData, length);

    EXPECT_EQ(status, CAIRO_STATUS_WRITE_ERROR);

}
