#include <gtest/gtest.h>

#include "util/hash.h"



namespace leveldb {



class HashTest_433 : public ::testing::Test {

protected:

    uint32_t seed = 0;

};



TEST_F(HashTest_433, EmptyStringHash_433) {

    const char* data = "";

    size_t n = 0;

    EXPECT_EQ(Hash(data, n, seed), seed);

}



TEST_F(HashTest_433, SingleCharHash_433) {

    const char* data = "a";

    size_t n = 1;

    uint32_t expected = seed ^ (n * 0xc6a4a793);

    expected += static_cast<uint8_t>(data[0]);

    expected *= 0xc6a4a793;

    expected ^= (expected >> 24);

    EXPECT_EQ(Hash(data, n, seed), expected);

}



TEST_F(HashTest_433, FourByteStringHash_433) {

    const char* data = "abcd";

    size_t n = 4;

    uint32_t expected = seed ^ (n * 0xc6a4a793);

    uint32_t w = DecodeFixed32(data);

    expected += w;

    expected *= 0xc6a4a793;

    expected ^= (expected >> 16);

    EXPECT_EQ(Hash(data, n, seed), expected);

}



TEST_F(HashTest_433, MultiFourByteStringHash_433) {

    const char* data = "abcdefgh";

    size_t n = 8;

    uint32_t expected = seed ^ (n * 0xc6a4a793);

    for (int i = 0; i < n; i += 4) {

        uint32_t w = DecodeFixed32(data + i);

        expected += w;

        expected *= 0xc6a4a793;

        expected ^= (expected >> 16);

    }

    EXPECT_EQ(Hash(data, n, seed), expected);

}



TEST_F(HashTest_433, NonFourByteStringHash_433) {

    const char* data = "abc";

    size_t n = 3;

    uint32_t expected = seed ^ (n * 0xc6a4a793);

    expected += static_cast<uint8_t>(data[2]) << 16;

    expected += static_cast<uint8_t>(data[1]) << 8;

    expected += static_cast<uint8_t>(data[0]);

    expected *= 0xc6a4a793;

    expected ^= (expected >> 24);

    EXPECT_EQ(Hash(data, n, seed), expected);

}



TEST_F(HashTest_433, LargeStringHash_433) {

    const char* data = "abcdefghijklmnopqrstuvwxyz";

    size_t n = 26;

    EXPECT_NE(Hash(data, n, seed), Hash(data, n, seed + 1));

}



} // namespace leveldb
