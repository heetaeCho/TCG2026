#include <gtest/gtest.h>

#include "util/coding.h"



class EncodeVarint32Test_440 : public ::testing::Test {

protected:

    char buffer[10];

};



TEST_F(EncodeVarint32Test_440, SingleByteEncoding_440) {

    uint32_t value = 63;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 1);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), value);

}



TEST_F(EncodeVarint32Test_440, TwoByteEncoding_440) {

    uint32_t value = 16383;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 2);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), (value | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[1]), (value >> 7));

}



TEST_F(EncodeVarint32Test_440, ThreeByteEncoding_440) {

    uint32_t value = 2097151;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 3);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), (value | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[1]), ((value >> 7) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[2]), (value >> 14));

}



TEST_F(EncodeVarint32Test_440, FourByteEncoding_440) {

    uint32_t value = 268435455;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 4);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), (value | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[1]), ((value >> 7) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[2]), ((value >> 14) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[3]), (value >> 21));

}



TEST_F(EncodeVarint32Test_440, FiveByteEncoding_440) {

    uint32_t value = 4294967295;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 5);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), (value | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[1]), ((value >> 7) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[2]), ((value >> 14) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[3]), ((value >> 21) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[4]), (value >> 28));

}



TEST_F(EncodeVarint32Test_440, BoundaryCondition_Zero_440) {

    uint32_t value = 0;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 1);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), value);

}



TEST_F(EncodeVarint32Test_440, BoundaryCondition_MaxValue_440) {

    uint32_t value = UINT32_MAX;

    char* result = leveldb::EncodeVarint32(buffer, value);

    EXPECT_EQ(result - buffer, 5);

    EXPECT_EQ(static_cast<uint8_t>(buffer[0]), (value | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[1]), ((value >> 7) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[2]), ((value >> 14) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[3]), ((value >> 21) | 128));

    EXPECT_EQ(static_cast<uint8_t>(buffer[4]), (value >> 28));

}
