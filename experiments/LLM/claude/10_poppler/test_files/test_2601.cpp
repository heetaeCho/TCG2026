#include <gtest/gtest.h>
#include "splash/SplashScreen.h"

// We need the SplashScreenParams structure
// Based on the poppler codebase, SplashScreenParams is defined in SplashTypes.h
#include "splash/SplashTypes.h"

class SplashScreenTest_2601 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with dispersed screen type
TEST_F(SplashScreenTest_2601, ConstructWithDispersedParams_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);
    delete screen;
}

// Test construction with clustered screen type
TEST_F(SplashScreenTest_2601, ConstructWithClusteredParams_2601) {
    SplashScreenParams params;
    params.type = splashScreenClustered;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);
    delete screen;
}

// Test construction with stochastic screen type
TEST_F(SplashScreenTest_2601, ConstructWithStochasticParams_2601) {
    SplashScreenParams params;
    params.type = splashScreenStochasticClustered;
    params.size = 2;
    params.dotRadius = 2;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);
    delete screen;
}

// Test copy() returns a non-null distinct object
TEST_F(SplashScreenTest_2601, CopyReturnsNonNull_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    SplashScreen *copied = screen->copy();

    ASSERT_NE(copied, nullptr);
    ASSERT_NE(copied, screen);

    delete copied;
    delete screen;
}

// Test that copy produces same test() results as original
TEST_F(SplashScreenTest_2601, CopyProducesSameTestResults_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    SplashScreen *copied = screen->copy();

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (unsigned char val = 0; val < 255; val += 50) {
                EXPECT_EQ(screen->test(x, y, val), copied->test(x, y, val));
            }
        }
    }

    delete copied;
    delete screen;
}

// Test test() returns 0 or 1
TEST_F(SplashScreenTest_2601, TestReturnsBinaryValue_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            for (unsigned char val = 0; val <= 255; val++) {
                int result = screen->test(x, y, val);
                EXPECT_TRUE(result == 0 || result == 1)
                    << "test(" << x << ", " << y << ", " << (int)val << ") returned " << result;
                if (val == 255) break; // avoid overflow
            }
        }
    }

    delete screen;
}

// Test with value 0 (black) - should generally return 1 (paint black)
TEST_F(SplashScreenTest_2601, TestWithValueZero_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    int result = screen->test(0, 0, 0);
    EXPECT_TRUE(result == 0 || result == 1);
    delete screen;
}

// Test with value 255 (white)
TEST_F(SplashScreenTest_2601, TestWithValueMax_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    int result = screen->test(0, 0, 255);
    EXPECT_TRUE(result == 0 || result == 1);
    delete screen;
}

// Test determinism - same inputs produce same outputs
TEST_F(SplashScreenTest_2601, TestIsDeterministic_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    int result1 = screen->test(3, 5, 128);
    int result2 = screen->test(3, 5, 128);
    EXPECT_EQ(result1, result2);

    delete screen;
}

// Test with large coordinates (wrapping behavior)
TEST_F(SplashScreenTest_2601, TestWithLargeCoordinates_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    // Large coordinates should still work (screen tiles/wraps)
    int result = screen->test(1000, 1000, 128);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

// Test with different sizes
TEST_F(SplashScreenTest_2601, ConstructWithDifferentSizes_2601) {
    for (int size = 1; size <= 4; size++) {
        SplashScreenParams params;
        params.type = splashScreenDispersed;
        params.size = size;
        params.dotRadius = 0;
        params.gamma = 1.0;
        params.blackThreshold = 0.0;
        params.whiteThreshold = 1.0;

        SplashScreen *screen = new SplashScreen(&params);
        ASSERT_NE(screen, nullptr);

        int result = screen->test(0, 0, 128);
        EXPECT_TRUE(result == 0 || result == 1);

        delete screen;
    }
}

// Test with different gamma values
TEST_F(SplashScreenTest_2601, ConstructWithDifferentGamma_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 2.2;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);

    int result = screen->test(0, 0, 128);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

// Test with black and white thresholds
TEST_F(SplashScreenTest_2601, TestWithBlackThreshold_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.5;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);

    int result = screen->test(0, 0, 10);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

TEST_F(SplashScreenTest_2601, TestWithWhiteThreshold_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 0.5;

    SplashScreen *screen = new SplashScreen(&params);
    ASSERT_NE(screen, nullptr);

    int result = screen->test(0, 0, 250);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

// Test that test() varies across different positions for mid-range values
TEST_F(SplashScreenTest_2601, TestVariesAcrossPositions_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    // For mid-range value, we expect some positions to return 0 and some 1
    int count0 = 0, count1 = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int result = screen->test(x, y, 128);
            if (result == 0) count0++;
            else count1++;
        }
    }

    // For a mid-range value, expect both 0s and 1s
    EXPECT_GT(count0, 0);
    EXPECT_GT(count1, 0);

    delete screen;
}

// Test clustered screen copy
TEST_F(SplashScreenTest_2601, CopyClusteredScreen_2601) {
    SplashScreenParams params;
    params.type = splashScreenClustered;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    SplashScreen *copied = screen->copy();

    ASSERT_NE(copied, nullptr);

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            EXPECT_EQ(screen->test(x, y, 100), copied->test(x, y, 100));
        }
    }

    delete copied;
    delete screen;
}

// Test negative coordinates (if applicable - may wrap or mask)
TEST_F(SplashScreenTest_2601, TestWithNegativeCoordinates_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    // Negative coordinates should still produce valid binary result due to masking
    int result = screen->test(-1, -1, 128);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

// Test with zero coordinates
TEST_F(SplashScreenTest_2601, TestWithZeroCoordinates_2601) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);

    int result = screen->test(0, 0, 128);
    EXPECT_TRUE(result == 0 || result == 1);

    delete screen;
}

// Test stochastic clustered screen copy consistency
TEST_F(SplashScreenTest_2601, CopyStochasticClusteredScreen_2601) {
    SplashScreenParams params;
    params.type = splashScreenStochasticClustered;
    params.size = 2;
    params.dotRadius = 2;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;

    SplashScreen *screen = new SplashScreen(&params);
    SplashScreen *copied = screen->copy();

    ASSERT_NE(copied, nullptr);

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            EXPECT_EQ(screen->test(x, y, 200), copied->test(x, y, 200));
        }
    }

    delete copied;
    delete screen;
}
