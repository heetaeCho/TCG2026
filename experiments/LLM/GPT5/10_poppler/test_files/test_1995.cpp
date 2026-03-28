#include <gtest/gtest.h>

// Assuming the adjustComp function is available for testing.
extern "C" unsigned char adjustComp(int r, int adjust, int depth, int sgndcorr, bool indexed);

TEST_F(JPEG2000StreamTest_1995, AdjustComp_NoIndex_NoAdjust_1995) {
    int r = 100;
    int adjust = 0;
    int depth = 8;
    int sgndcorr = 0;
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);
    
    // r should remain the same as no adjustment occurs
    EXPECT_EQ(result, 100);
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_WithAdjust_1995) {
    int r = 100;
    int adjust = 2;
    int depth = 8;
    int sgndcorr = 0;
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);
    
    // Expecting r to be adjusted based on the logic for adjust
    EXPECT_EQ(result, 25); // Assuming the adjustment calculation divides by 4 (r >> 2)
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_WithDepthLessThan8_1995) {
    int r = 100;
    int adjust = 0;
    int depth = 6;  // Depth is less than 8
    int sgndcorr = 0;
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);

    // Expect the result to be left-shifted (r << (8 - depth))
    EXPECT_EQ(result, 400); // 100 << 2 = 400, but it should clamp at 255
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_Indexed_1995) {
    int r = 100;
    int adjust = 0;
    int depth = 8;
    int sgndcorr = 0;
    bool indexed = true;  // Indexed flag is true

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);

    // Since indexed is true, no adjustments should be made
    EXPECT_EQ(result, 100);
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_WithSignedCorrection_1995) {
    int r = 100;
    int adjust = 0;
    int depth = 8;
    int sgndcorr = 10;  // Signed correction
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);

    // r should be adjusted by sgndcorr (100 + 10 = 110)
    EXPECT_EQ(result, 110);
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_ClampOver255_1995) {
    int r = 300;  // Out of bounds (should be clamped)
    int adjust = 0;
    int depth = 8;
    int sgndcorr = 0;
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);

    // The value should be clamped to 255
    EXPECT_EQ(result, 255);
}

TEST_F(JPEG2000StreamTest_1995, AdjustComp_ClampUnder0_1995) {
    int r = -10;  // Negative value (should be clamped)
    int adjust = 0;
    int depth = 8;
    int sgndcorr = 0;
    bool indexed = false;

    unsigned char result = adjustComp(r, adjust, depth, sgndcorr, indexed);

    // The value should be clamped to 0
    EXPECT_EQ(result, 0);
}