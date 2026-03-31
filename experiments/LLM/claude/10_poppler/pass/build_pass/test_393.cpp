#include <gtest/gtest.h>

// Include the header containing colToByte
#include "GfxState.h"

class ColToByteTest_393 : public ::testing::Test {
protected:
};

// Test that zero input produces zero output
TEST_F(ColToByteTest_393, ZeroInput_393) {
    GfxColorComp input = 0;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 0);
}

// Test that the maximum GfxColorComp value (65535) maps to 255
TEST_F(ColToByteTest_393, MaxInputMapsTo255_393) {
    GfxColorComp input = 65535;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 255);
}

// Test that a mid-range value maps correctly
// 32768 (0x8000) should map approximately to 128
TEST_F(ColToByteTest_393, MidRangeInput_393) {
    GfxColorComp input = 32768;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 128);
}

// Test that value 256 maps to 1 (first value that should produce 1)
TEST_F(ColToByteTest_393, SmallValueMapsToOne_393) {
    // 256 * 256 - 256 + 0x8000 = 65536 - 256 + 32768 = 98048
    // 98048 >> 16 = 1
    GfxColorComp input = 256;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 1);
}

// Test that value 1 maps to 0 (too small to reach 1)
TEST_F(ColToByteTest_393, VerySmallInputMapsToZero_393) {
    GfxColorComp input = 1;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 0);
}

// Test known quarter value: 16384 should map to approximately 64
TEST_F(ColToByteTest_393, QuarterRangeInput_393) {
    GfxColorComp input = 16384;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 64);
}

// Test known three-quarter value: 49152 should map to approximately 192
TEST_F(ColToByteTest_393, ThreeQuarterRangeInput_393) {
    GfxColorComp input = 49152;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 192);
}

// Test that result is always in [0, 255] range for various inputs
TEST_F(ColToByteTest_393, ResultInValidByteRange_393) {
    for (int i = 0; i <= 65535; i += 1000) {
        GfxColorComp input = static_cast<GfxColorComp>(i);
        unsigned char result = colToByte(input);
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 255);
    }
}

// Test that the function is monotonically non-decreasing
TEST_F(ColToByteTest_393, MonotonicallyNonDecreasing_393) {
    unsigned char prev = colToByte(0);
    for (int i = 1; i <= 65535; i += 100) {
        GfxColorComp input = static_cast<GfxColorComp>(i);
        unsigned char curr = colToByte(input);
        EXPECT_GE(curr, prev) << "Failed at input " << i;
        prev = curr;
    }
}

// Test specific boundary: value 128 (near zero boundary)
TEST_F(ColToByteTest_393, BoundaryValue128_393) {
    GfxColorComp input = 128;
    unsigned char result = colToByte(input);
    // (128 << 8) - 128 + 0x8000 = 32768 - 128 + 32768 = 65408
    // 65408 >> 16 = 0
    EXPECT_EQ(result, 0);
}

// Test that 65535 maps to exactly 255
TEST_F(ColToByteTest_393, MaxValueExact_393) {
    GfxColorComp input = 65535;
    // (65535 << 8) - 65535 + 0x8000 = 16776960 - 65535 + 32768 = 16744193
    // 16744193 >> 16 = 255
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 255);
}

// Test value just below maximum
TEST_F(ColToByteTest_393, JustBelowMax_393) {
    GfxColorComp input = 65534;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 255);
}

// Test value that should produce 127
TEST_F(ColToByteTest_393, ValueProducing127_393) {
    // Want (x << 8) - x + 0x8000 to be in [127 * 65536, 128 * 65536)
    // 127 * 65536 = 8323072
    // (x * 255) + 32768 >= 8323072 => x >= (8323072 - 32768) / 255 = 32512.17
    GfxColorComp input = 32513;
    unsigned char result = colToByte(input);
    EXPECT_EQ(result, 127);
}
