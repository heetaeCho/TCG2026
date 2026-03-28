#include <gtest/gtest.h>

#include "gmem.h"



// Test fixture for gmallocn_checkoverflow tests

class GMemTest_13 : public ::testing::Test {

protected:

    void *result;

};



TEST_F(GMemTest_13, AllocateSingleByte_13) {

    result = gmallocn_checkoverflow(1, 1);

    EXPECT_NE(result, nullptr);

    free(result);

}



TEST_F(GMemTest_13, AllocateMultipleBytes_13) {

    result = gmallocn_checkoverflow(10, 1);

    EXPECT_NE(result, nullptr);

    free(result);

}



TEST_F(GMemTest_13, AllocateLargeBlock_13) {

    result = gmallocn_checkoverflow(1024, 1024);

    EXPECT_NE(result, nullptr);

    free(result);

}



TEST_F(GMemTest_13, ZeroSizeAllocation_13) {

    result = gmallocn_checkoverflow(0, 1);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_13, NegativeCount_13) {

    result = gmallocn_checkoverflow(-1, 1);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_13, NegativeSize_13) {

    result = gmallocn_checkoverflow(1, -1);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_13, OverflowCondition_13) {

    // This test assumes that the multiplication of count and size overflows

    result = gmallocn_checkoverflow(INT_MAX, 2);

    EXPECT_EQ(result, nullptr);

}
