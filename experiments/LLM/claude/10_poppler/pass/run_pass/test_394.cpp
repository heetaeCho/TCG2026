#include <gtest/gtest.h>

// Include the header that contains colToShort
#include "GfxState.h"

// Test normal operation with a typical value
TEST(ColToShortTest_394, NormalValue_394) {
    GfxColorComp input = 12345;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, static_cast<unsigned short>(input));
}

// Test with zero value
TEST(ColToShortTest_394, ZeroValue_394) {
    GfxColorComp input = 0;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 0);
}

// Test with value 1
TEST(ColToShortTest_394, OneValue_394) {
    GfxColorComp input = 1;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 1);
}

// Test with maximum unsigned short value
TEST(ColToShortTest_394, MaxUnsignedShortValue_394) {
    GfxColorComp input = 65535;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 65535);
}

// Test with a mid-range value
TEST(ColToShortTest_394, MidRangeValue_394) {
    GfxColorComp input = 32768;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 32768);
}

// Test with value 255 (common 8-bit max)
TEST(ColToShortTest_394, Value255_394) {
    GfxColorComp input = 255;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 255);
}

// Test with value 256
TEST(ColToShortTest_394, Value256_394) {
    GfxColorComp input = 256;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 256);
}

// Test that the cast produces the expected unsigned short
TEST(ColToShortTest_394, CastBehavior_394) {
    GfxColorComp input = 50000;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, static_cast<unsigned short>(50000));
}

// Test with value just below max unsigned short
TEST(ColToShortTest_394, MaxMinusOne_394) {
    GfxColorComp input = 65534;
    unsigned short result = colToShort(input);
    EXPECT_EQ(result, 65534);
}

// Test multiple sequential calls produce consistent results
TEST(ColToShortTest_394, ConsistentResults_394) {
    GfxColorComp input = 1000;
    unsigned short result1 = colToShort(input);
    unsigned short result2 = colToShort(input);
    EXPECT_EQ(result1, result2);
}
