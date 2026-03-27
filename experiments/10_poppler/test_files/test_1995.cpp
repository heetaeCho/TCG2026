#include <gtest/gtest.h>



// Assuming adjustComp is part of a class or namespace for testing purposes.

// Since it's a static inline function, we'll assume it's in a namespace or global scope for simplicity.



namespace {



unsigned char adjustComp(int r, int adjust, int depth, int sgndcorr, bool indexed) {

    if (!indexed) {

        r += sgndcorr;

        if (adjust) {

            r = (r >> adjust) + ((r >> (adjust - 1)) % 2);

        } else if (depth < 8) {

            r = r << (8 - depth);

        }

    }

    if (unlikely(r > 255)) {

        r = 255;

    }

    return r;

}



} // namespace



// Test suite for the adjustComp function

class AdjustCompTest_1995 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(AdjustCompTest_1995, NormalOperation_1995) {

    EXPECT_EQ(adjustComp(100, 0, 8, 0, false), 100);

    EXPECT_EQ(adjustComp(128, 1, 8, 0, false), 64 + (64 % 2));

    EXPECT_EQ(adjustComp(50, 0, 4, 0, false), 50 << (8 - 4));

}



TEST_F(AdjustCompTest_1995, BoundaryConditions_1995) {

    EXPECT_EQ(adjustComp(0, 0, 8, 0, false), 0);

    EXPECT_EQ(adjustComp(255, 0, 8, 0, false), 255);

    EXPECT_EQ(adjustComp(256, 0, 8, 0, false), 255); // Clipping to 255

}



TEST_F(AdjustCompTest_1995, SignedCorrection_1995) {

    EXPECT_EQ(adjustComp(-10, 0, 8, 10, false), 0);

    EXPECT_EQ(adjustComp(10, 0, 8, -10, false), 0);

}



TEST_F(AdjustCompTest_1995, IndexedFlagTrue_1995) {

    EXPECT_EQ(adjustComp(100, 0, 8, 0, true), 100); // No change if indexed is true

    EXPECT_EQ(adjustComp(-100, 3, 8, 100, true), -100); // No change if indexed is true

}



TEST_F(AdjustCompTest_1995, DepthLessThanEight_1995) {

    EXPECT_EQ(adjustComp(16, 0, 4, 0, false), 16 << (8 - 4)); // 256

    EXPECT_EQ(adjustComp(31, 0, 5, 0, false), 31 << (8 - 5)); // 992 -> 255 (clipped)

}



TEST_F(AdjustCompTest_1995, AdjustGreaterThanZero_1995) {

    EXPECT_EQ(adjustComp(128, 1, 8, 0, false), 64 + (64 % 2));

    EXPECT_EQ(adjustComp(255, 2, 8, 0, false), 63 + (31 % 2)); // Clipped to 255

}
