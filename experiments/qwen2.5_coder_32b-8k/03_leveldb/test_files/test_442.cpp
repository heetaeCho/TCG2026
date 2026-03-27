#include <gtest/gtest.h>

#include "util/coding.h"



namespace leveldb {



class EncodeVarint64Test_442 : public ::testing::Test {

protected:

    char buffer_[10]; // Sufficiently large buffer for encoding

};



TEST_F(EncodeVarint64Test_442, SmallValueEncoding_442) {

    uint64_t value = 3;

    char* end = EncodeVarint64(buffer_, value);

    EXPECT_EQ(end - buffer_, 1); // Should use one byte

    EXPECT_EQ(static_cast<uint8_t>(buffer_[0]), 3); // Value should be stored directly

}



TEST_F(EncodeVarint64Test_442, MediumValueEncoding_442) {

    uint64_t value = 128;

    char* end = EncodeVarint64(buffer_, value);

    EXPECT_EQ(end - buffer_, 2); // Should use two bytes

    EXPECT_EQ(static_cast<uint8_t>(buffer_[0]), 128 | 128); // First byte with continuation bit set

    EXPECT_EQ(static_cast<uint8_t>(buffer_[1]), 1); // Second byte with the actual value

}



TEST_F(EncodeVarint64Test_442, LargeValueEncoding_442) {

    uint64_t value = 0x123456789ABCDEF0;

    char* end = EncodeVarint64(buffer_, value);

    EXPECT_EQ(end - buffer_, 10); // Should use ten bytes for this large value

    EXPECT_EQ(static_cast<uint8_t>(buffer_[0]), 0xF0 | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[1]), 0xDE | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[2]), 0xBC | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[3]), 0x9A | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[4]), 0x78 | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[5]), 0x56 | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[6]), 0x34 | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[7]), 0x12 | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[8]), 0); // No continuation bit set

}



TEST_F(EncodeVarint64Test_442, MaxValueEncoding_442) {

    uint64_t value = UINT64_MAX;

    char* end = EncodeVarint64(buffer_, value);

    EXPECT_EQ(end - buffer_, 10); // Should use ten bytes for the max value

    EXPECT_EQ(static_cast<uint8_t>(buffer_[0]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[1]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[2]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[3]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[4]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[5]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[6]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[7]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[8]), 0xFF | 128);

    EXPECT_EQ(static_cast<uint8_t>(buffer_[9]), 0x01); // No continuation bit set

}



}  // namespace leveldb
