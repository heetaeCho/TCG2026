#include <gtest/gtest.h>
#include "GfxState.h"

// Type alias for clarity
using GfxColorComp = decltype(byteToCol(0));

class ByteToColTest_392 : public ::testing::Test {
protected:
};

// Test with minimum byte value (0)
TEST_F(ByteToColTest_392, ZeroInput_392) {
    GfxColorComp result = byteToCol(0);
    // (0 << 8) + 0 + (0 >> 7) = 0
    EXPECT_EQ(result, 0);
}

// Test with maximum byte value (255)
TEST_F(ByteToColTest_392, MaxInput_392) {
    GfxColorComp result = byteToCol(255);
    // (255 << 8) + 255 + (255 >> 7) = 65280 + 255 + 1 = 65536
    EXPECT_EQ(result, static_cast<GfxColorComp>(65536));
}

// Test with value 1
TEST_F(ByteToColTest_392, InputOne_392) {
    GfxColorComp result = byteToCol(1);
    // (1 << 8) + 1 + (1 >> 7) = 256 + 1 + 0 = 257
    EXPECT_EQ(result, static_cast<GfxColorComp>(257));
}

// Test with value 127 (just below the threshold where x >> 7 becomes 1)
TEST_F(ByteToColTest_392, Input127_392) {
    GfxColorComp result = byteToCol(127);
    // (127 << 8) + 127 + (127 >> 7) = 32512 + 127 + 0 = 32639
    EXPECT_EQ(result, static_cast<GfxColorComp>(32639));
}

// Test with value 128 (where x >> 7 becomes 1)
TEST_F(ByteToColTest_392, Input128_392) {
    GfxColorComp result = byteToCol(128);
    // (128 << 8) + 128 + (128 >> 7) = 32768 + 128 + 1 = 32897
    EXPECT_EQ(result, static_cast<GfxColorComp>(32897));
}

// Test with midpoint value 64
TEST_F(ByteToColTest_392, Input64_392) {
    GfxColorComp result = byteToCol(64);
    // (64 << 8) + 64 + (64 >> 7) = 16384 + 64 + 0 = 16448
    EXPECT_EQ(result, static_cast<GfxColorComp>(16448));
}

// Test with value 192
TEST_F(ByteToColTest_392, Input192_392) {
    GfxColorComp result = byteToCol(192);
    // (192 << 8) + 192 + (192 >> 7) = 49152 + 192 + 1 = 49345
    EXPECT_EQ(result, static_cast<GfxColorComp>(49345));
}

// Test with value 254
TEST_F(ByteToColTest_392, Input254_392) {
    GfxColorComp result = byteToCol(254);
    // (254 << 8) + 254 + (254 >> 7) = 65024 + 254 + 1 = 65279
    EXPECT_EQ(result, static_cast<GfxColorComp>(65279));
}

// Test with value 2
TEST_F(ByteToColTest_392, InputTwo_392) {
    GfxColorComp result = byteToCol(2);
    // (2 << 8) + 2 + (2 >> 7) = 512 + 2 + 0 = 514
    EXPECT_EQ(result, static_cast<GfxColorComp>(514));
}

// Test monotonicity: larger input should produce larger output
TEST_F(ByteToColTest_392, Monotonicity_392) {
    for (unsigned int i = 0; i < 255; ++i) {
        GfxColorComp lower = byteToCol(static_cast<unsigned char>(i));
        GfxColorComp upper = byteToCol(static_cast<unsigned char>(i + 1));
        EXPECT_LT(lower, upper) << "Failed monotonicity at i=" << i;
    }
}

// Test that zero maps to zero and 255 maps to maximum (65536)
TEST_F(ByteToColTest_392, BoundaryMapping_392) {
    EXPECT_EQ(byteToCol(0), static_cast<GfxColorComp>(0));
    EXPECT_EQ(byteToCol(255), static_cast<GfxColorComp>(65536));
}

// Test value 129
TEST_F(ByteToColTest_392, Input129_392) {
    GfxColorComp result = byteToCol(129);
    // (129 << 8) + 129 + (129 >> 7) = 33024 + 129 + 1 = 33154
    EXPECT_EQ(result, static_cast<GfxColorComp>(33154));
}
