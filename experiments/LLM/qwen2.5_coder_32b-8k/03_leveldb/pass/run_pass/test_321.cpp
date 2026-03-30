#include <gtest/gtest.h>

#include "util/crc32c.h"



using namespace leveldb::crc32c;



class Crc32cMaskTest_321 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(Crc32cMaskTest_321, MaskNormalOperation_321) {

    uint32_t crc = 0x12345678;

    uint32_t expected_masked_value = ((crc >> 15) | (crc << 17)) + kMaskDelta;

    EXPECT_EQ(Mask(crc), expected_masked_value);

}



TEST_F(Crc32cMaskTest_321, MaskBoundaryConditionZeroCrc_321) {

    uint32_t crc = 0x00000000;

    uint32_t expected_masked_value = kMaskDelta;

    EXPECT_EQ(Mask(crc), expected_masked_value);

}



TEST_F(Crc32cMaskTest_321, MaskBoundaryConditionMaxCrc_321) {

    uint32_t crc = 0xFFFFFFFF;

    uint32_t expected_masked_value = ((crc >> 15) | (crc << 17)) + kMaskDelta;

    EXPECT_EQ(Mask(crc), expected_masked_value);

}



TEST_F(Crc32cMaskTest_321, MaskBoundaryConditionHalfMaxCrc_321) {

    uint32_t crc = 0x80000000;

    uint32_t expected_masked_value = ((crc >> 15) | (crc << 17)) + kMaskDelta;

    EXPECT_EQ(Mask(crc), expected_masked_value);

}
