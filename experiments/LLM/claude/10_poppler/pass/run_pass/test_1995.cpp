#include <gtest/gtest.h>

// Reproduce the function under test exactly as provided
static inline unsigned char adjustComp(int r, int adjust, int depth, int sgndcorr, bool indexed) {
    if (!indexed) {
        r += sgndcorr;
        if (adjust) {
            r = (r >> adjust) + ((r >> (adjust - 1)) % 2);
        } else if (depth < 8) {
            r = r << (8 - depth);
        }
    }
    if (r > 255) {
        r = 255;
    }
    return r;
}

// Normal operation tests

TEST(AdjustCompTest_1995, IndexedPassthrough_1995) {
    // When indexed is true, r should be returned as-is (no adjustments),
    // clamped to 255
    unsigned char result = adjustComp(100, 0, 8, 0, true);
    EXPECT_EQ(result, 100);
}

TEST(AdjustCompTest_1995, IndexedPassthroughWithSgndcorr_1995) {
    // When indexed is true, sgndcorr should NOT be applied
    unsigned char result = adjustComp(100, 0, 8, 50, true);
    EXPECT_EQ(result, 100);
}

TEST(AdjustCompTest_1995, IndexedPassthroughWithAdjust_1995) {
    // When indexed is true, adjust should NOT be applied
    unsigned char result = adjustComp(100, 2, 8, 0, true);
    EXPECT_EQ(result, 100);
}

TEST(AdjustCompTest_1995, NotIndexedSgndcorrApplied_1995) {
    // When not indexed, sgndcorr is added to r
    // adjust=0, depth=8, so no shifting
    unsigned char result = adjustComp(100, 0, 8, 10, false);
    EXPECT_EQ(result, 110);
}

TEST(AdjustCompTest_1995, NotIndexedAdjustShiftRight_1995) {
    // When not indexed with adjust > 0, r is right-shifted and rounded
    // r=100, sgndcorr=0 => r=100
    // adjust=2: r = (100 >> 2) + ((100 >> 1) % 2) = 25 + (50 % 2) = 25 + 0 = 25
    unsigned char result = adjustComp(100, 2, 8, 0, false);
    EXPECT_EQ(result, 25);
}

TEST(AdjustCompTest_1995, NotIndexedAdjustWithRounding_1995) {
    // r=101, sgndcorr=0 => r=101
    // adjust=2: r = (101 >> 2) + ((101 >> 1) % 2) = 25 + (50 % 2) = 25 + 0 = 25
    unsigned char result = adjustComp(101, 2, 8, 0, false);
    EXPECT_EQ(result, 25);
}

TEST(AdjustCompTest_1995, NotIndexedAdjustWithRoundingOdd_1995) {
    // r=102, sgndcorr=0 => r=102
    // adjust=2: r = (102 >> 2) + ((102 >> 1) % 2) = 25 + (51 % 2) = 25 + 1 = 26
    unsigned char result = adjustComp(102, 2, 8, 0, false);
    EXPECT_EQ(result, 26);
}

TEST(AdjustCompTest_1995, NotIndexedDepthLessThan8LeftShift_1995) {
    // When not indexed, adjust=0, depth<8: r is left-shifted by (8-depth)
    // r=5, sgndcorr=0, depth=4 => r = 5 << 4 = 80
    unsigned char result = adjustComp(5, 0, 4, 0, false);
    EXPECT_EQ(result, 80);
}

TEST(AdjustCompTest_1995, NotIndexedDepth1LeftShift_1995) {
    // depth=1: r = 1 << 7 = 128
    unsigned char result = adjustComp(1, 0, 1, 0, false);
    EXPECT_EQ(result, 128);
}

TEST(AdjustCompTest_1995, NotIndexedDepth7LeftShift_1995) {
    // depth=7: r = 63 << 1 = 126
    unsigned char result = adjustComp(63, 0, 7, 0, false);
    EXPECT_EQ(result, 126);
}

// Boundary condition tests

TEST(AdjustCompTest_1995, ClampTo255WhenExceeds_1995) {
    // Result exceeds 255, should be clamped
    unsigned char result = adjustComp(300, 0, 8, 0, false);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, ClampTo255WhenExceedsIndexed_1995) {
    // Even when indexed, values > 255 should be clamped
    unsigned char result = adjustComp(300, 0, 8, 0, true);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, Exactly255_1995) {
    unsigned char result = adjustComp(255, 0, 8, 0, false);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, Exactly255Indexed_1995) {
    unsigned char result = adjustComp(255, 0, 8, 0, true);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, ZeroValue_1995) {
    unsigned char result = adjustComp(0, 0, 8, 0, false);
    EXPECT_EQ(result, 0);
}

TEST(AdjustCompTest_1995, ZeroValueIndexed_1995) {
    unsigned char result = adjustComp(0, 0, 8, 0, true);
    EXPECT_EQ(result, 0);
}

TEST(AdjustCompTest_1995, SgndcorrCausesOverflow_1995) {
    // r=200, sgndcorr=100 => 300, clamped to 255
    unsigned char result = adjustComp(200, 0, 8, 100, false);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, DepthShiftCausesOverflow_1995) {
    // r=15, depth=4 => r = 15 << 4 = 240
    unsigned char result = adjustComp(15, 0, 4, 0, false);
    EXPECT_EQ(result, 240);
}

TEST(AdjustCompTest_1995, DepthShiftExceeds255_1995) {
    // r=16, depth=4 => r = 16 << 4 = 256, clamped to 255
    unsigned char result = adjustComp(16, 0, 4, 0, false);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, NegativeRWithSgndcorr_1995) {
    // Negative r + sgndcorr brings it to positive range
    // r=-128, sgndcorr=128 => r=0, depth=8, adjust=0
    unsigned char result = adjustComp(-128, 0, 8, 128, false);
    EXPECT_EQ(result, 0);
}

TEST(AdjustCompTest_1995, NegativeResultWraps_1995) {
    // r=-1, sgndcorr=0, indexed=true
    // Negative value cast to unsigned char
    // The function returns unsigned char, so -1 would wrap.
    // But the clamp only catches > 255. Let's see: -1 > 255 is false (as int), so it returns (unsigned char)-1 = 255
    unsigned char result = adjustComp(-1, 0, 8, 0, true);
    EXPECT_EQ(result, 255);
}

TEST(AdjustCompTest_1995, AdjustEquals1_1995) {
    // adjust=1: r = (r >> 1) + ((r >> 0) % 2) = r/2 + r%2
    // r=7: 3 + 1 = 4
    unsigned char result = adjustComp(7, 1, 8, 0, false);
    EXPECT_EQ(result, 4);
}

TEST(AdjustCompTest_1995, AdjustEquals1Even_1995) {
    // r=8: (8 >> 1) + ((8 >> 0) % 2) = 4 + 0 = 4
    unsigned char result = adjustComp(8, 1, 8, 0, false);
    EXPECT_EQ(result, 4);
}

TEST(AdjustCompTest_1995, LargeAdjust_1995) {
    // adjust=8: r=255 => (255 >> 8) + ((255 >> 7) % 2) = 0 + (1 % 2) = 1
    unsigned char result = adjustComp(255, 8, 16, 0, false);
    EXPECT_EQ(result, 1);
}

TEST(AdjustCompTest_1995, Depth8NoShift_1995) {
    // depth exactly 8, adjust=0: no shift applied
    unsigned char result = adjustComp(42, 0, 8, 0, false);
    EXPECT_EQ(result, 42);
}

TEST(AdjustCompTest_1995, DepthGreaterThan8NoShift_1995) {
    // depth > 8, adjust=0: depth < 8 is false, so no shift
    unsigned char result = adjustComp(42, 0, 10, 0, false);
    EXPECT_EQ(result, 42);
}

TEST(AdjustCompTest_1995, SgndcorrAndAdjustCombined_1995) {
    // r=100, sgndcorr=28 => 128, adjust=2
    // (128 >> 2) + ((128 >> 1) % 2) = 32 + (64 % 2) = 32 + 0 = 32
    unsigned char result = adjustComp(100, 2, 10, 28, false);
    EXPECT_EQ(result, 32);
}

TEST(AdjustCompTest_1995, SgndcorrAndDepthShiftCombined_1995) {
    // r=3, sgndcorr=1 => 4, adjust=0, depth=6
    // r = 4 << 2 = 16
    unsigned char result = adjustComp(3, 0, 6, 1, false);
    EXPECT_EQ(result, 16);
}

TEST(AdjustCompTest_1995, IndexedNegativeSmallValue_1995) {
    // indexed, r = -5: negative int cast to unsigned char
    // -5 > 255 is false (int comparison), so returns (unsigned char)(-5) = 251
    unsigned char result = adjustComp(-5, 0, 8, 0, true);
    EXPECT_EQ(result, 251);
}

TEST(AdjustCompTest_1995, Depth2ShiftBy6_1995) {
    // r=3, depth=2, adjust=0, sgndcorr=0
    // r = 3 << 6 = 192
    unsigned char result = adjustComp(3, 0, 2, 0, false);
    EXPECT_EQ(result, 192);
}

TEST(AdjustCompTest_1995, AdjustPreventsDepthShift_1995) {
    // When adjust > 0, depth shift is not applied even if depth < 8
    // r=5, adjust=1, depth=4, sgndcorr=0
    // r = (5 >> 1) + ((5 >> 0) % 2) = 2 + 1 = 3
    unsigned char result = adjustComp(5, 1, 4, 0, false);
    EXPECT_EQ(result, 3);
}
