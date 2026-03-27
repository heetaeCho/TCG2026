#include <gtest/gtest.h>

#include "util/coding.cc"



namespace leveldb {



class PutVarint32Test_441 : public ::testing::Test {

protected:

    std::string dst;

};



TEST_F(PutVarint32Test_441, PutSingleByteValue_441) {

    uint32_t value = 1;

    PutVarint32(&dst, value);

    EXPECT_EQ(dst.size(), 1);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 1);

}



TEST_F(PutVarint32Test_441, PutMultiByteValue_441) {

    uint32_t value = 128;

    PutVarint32(&dst, value);

    EXPECT_EQ(dst.size(), 2);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 128);

    EXPECT_EQ(static_cast<unsigned char>(dst[1]), 1);

}



TEST_F(PutVarint32Test_441, PutMaxValue_441) {

    uint32_t value = 0xFFFFFFFF;

    PutVarint32(&dst, value);

    EXPECT_EQ(dst.size(), 5);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 255);

    EXPECT_EQ(static_cast<unsigned char>(dst[1]), 255);

    EXPECT_EQ(static_cast<unsigned char>(dst[2]), 255);

    EXPECT_EQ(static_cast<unsigned char>(dst[3]), 255);

    EXPECT_EQ(static_cast<unsigned char>(dst[4]), 15);

}



TEST_F(PutVarint32Test_441, PutZeroValue_441) {

    uint32_t value = 0;

    PutVarint32(&dst, value);

    EXPECT_EQ(dst.size(), 1);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0);

}



TEST_F(PutVarint32Test_441, AppendToNonEmptyString_441) {

    dst = "initial";

    uint32_t value = 64;

    PutVarint32(&dst, value);

    EXPECT_EQ(dst.size(), 8); // 5 bytes for varint + 3 initial characters

    EXPECT_EQ(dst.substr(0, 7), "initial@"); // '@' is the varint representation of 64

}



} // namespace leveldb
