#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "port/port_stdcxx.h"



using namespace leveldb::port;



class Snappy_GetUncompressedLengthTest_37 : public ::testing::Test {

protected:

    size_t result;

};



TEST_F(Snappy_GetUncompressedLengthTest_37, ValidCompressedData_37) {

    const char* input = "\x80\x2f\x2d\xa2";

    size_t length = 4;

    EXPECT_TRUE(Snappy_GetUncompressedLength(input, length, &result));

    // Assuming a known uncompressed length for the test data

    EXPECT_EQ(result, 10);

}



TEST_F(Snappy_GetUncompressedLengthTest_37, InvalidCompressedData_37) {

    const char* input = "invalid";

    size_t length = 7;

    EXPECT_FALSE(Snappy_GetUncompressedLength(input, length, &result));

}



TEST_F(Snappy_GetUncompressedLengthTest_37, ZeroLengthInput_37) {

    const char* input = "";

    size_t length = 0;

    EXPECT_FALSE(Snappy_GetUncompressedLength(input, length, &result));

}



TEST_F(Snappy_GetUncompressedLengthTest_37, NullInputPointer_37) {

    const char* input = nullptr;

    size_t length = 10;

    EXPECT_FALSE(Snappy_GetUncompressedLength(input, length, &result));

}



TEST_F(Snappy_GetUncompressedLengthTest_37, NullResultPointer_37) {

    const char* input = "\x80\x2f\x2d\xa2";

    size_t length = 4;

    EXPECT_FALSE(Snappy_GetUncompressedLength(input, length, nullptr));

}
