#include <gtest/gtest.h>

#include "util/coding.h"



namespace {



class CodingTest_45 : public ::testing::Test {

protected:

    uint8_t buffer_[8];



    void SetUp() override {

        // Initialize buffer with known values for testing

        buffer_[0] = 0x12;

        buffer_[1] = 0x34;

        buffer_[2] = 0x56;

        buffer_[3] = 0x78;

        buffer_[4] = 0x9A;

        buffer_[5] = 0xBC;

        buffer_[6] = 0xDE;

        buffer_[7] = 0xF0;

    }

};



TEST_F(CodingTest_45, DecodeFixed64_NormalOperation_45) {

    uint64_t expected_value = 0x123456789ABCDEF0;

    uint64_t result = leveldb::DecodeFixed64(reinterpret_cast<const char*>(buffer_));

    EXPECT_EQ(result, expected_value);

}



TEST_F(CodingTest_45, DecodeFixed64_AllZeros_45) {

    memset(buffer_, 0, sizeof(buffer_));

    uint64_t expected_value = 0x0;

    uint64_t result = leveldb::DecodeFixed64(reinterpret_cast<const char*>(buffer_));

    EXPECT_EQ(result, expected_value);

}



TEST_F(CodingTest_45, DecodeFixed64_AllOnes_45) {

    memset(buffer_, 0xFF, sizeof(buffer_));

    uint64_t expected_value = 0xFFFFFFFFFFFFFFFF;

    uint64_t result = leveldb::DecodeFixed64(reinterpret_cast<const char*>(buffer_));

    EXPECT_EQ(result, expected_value);

}



TEST_F(CodingTest_45, DecodeFixed64_MaxValue_45) {

    buffer_[0] = 0xFF;

    buffer_[1] = 0xFF;

    buffer_[2] = 0xFF;

    buffer_[3] = 0xFF;

    buffer_[4] = 0xFF;

    buffer_[5] = 0xFF;

    buffer_[6] = 0xFF;

    buffer_[7] = 0x7F;

    uint64_t expected_value = 0x7FFFFFFFFFFFFFFF;

    uint64_t result = leveldb::DecodeFixed64(reinterpret_cast<const char*>(buffer_));

    EXPECT_EQ(result, expected_value);

}



TEST_F(CodingTest_45, DecodeFixed64_MinValue_45) {

    buffer_[0] = 0x00;

    buffer_[1] = 0x00;

    buffer_[2] = 0x00;

    buffer_[3] = 0x00;

    buffer_[4] = 0x00;

    buffer_[5] = 0x00;

    buffer_[6] = 0x00;

    buffer_[7] = 0x80;

    uint64_t expected_value = 0x8000000000000000;

    uint64_t result = leveldb::DecodeFixed64(reinterpret_cast<const char*>(buffer_));

    EXPECT_EQ(result, expected_value);

}



} // namespace
