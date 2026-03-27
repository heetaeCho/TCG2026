#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/coding.h"

#include <string>



using namespace leveldb;



class PutVarint64Test_443 : public ::testing::Test {

protected:

    std::string dst;

};



TEST_F(PutVarint64Test_443, NormalOperation_SmallValue_443) {

    uint64_t value = 1;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 1);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 1);

}



TEST_F(PutVarint64Test_443, NormalOperation_MediumValue_443) {

    uint64_t value = 255;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 2);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 255);

    EXPECT_EQ(static_cast<unsigned char>(dst[1]), 1);

}



TEST_F(PutVarint64Test_443, NormalOperation_MaxValue_443) {

    uint64_t value = UINT64_MAX;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 10);

    EXPECT_EQ(static_cast<unsigned char>(dst[9]), 1);

}



TEST_F(PutVarint64Test_443, BoundaryCondition_Zero_443) {

    uint64_t value = 0;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 1);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0);

}



TEST_F(PutVarint64Test_443, BoundaryCondition_MaxSingleByte_443) {

    uint64_t value = 127;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 1);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 127);

}



TEST_F(PutVarint64Test_443, BoundaryCondition_MinMultiByte_443) {

    uint64_t value = 128;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 2);

    EXPECT_EQ(static_cast<unsigned char>(dst[0]), 128);

    EXPECT_EQ(static_cast<unsigned char>(dst[1]), 1);

}



TEST_F(PutVarint64Test_443, BoundaryCondition_MaxMultiByte_443) {

    uint64_t value = (1LL << 56) - 1;

    PutVarint64(&dst, value);

    EXPECT_EQ(dst.size(), 9);

    for (size_t i = 0; i < 8; ++i) {

        EXPECT_EQ(static_cast<unsigned char>(dst[i]), 255);

    }

    EXPECT_EQ(static_cast<unsigned char>(dst[8]), 1);

}
