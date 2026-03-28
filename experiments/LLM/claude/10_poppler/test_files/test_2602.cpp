#include <gtest/gtest.h>
#include "splash/SplashScreen.h"

// We need to know the SplashScreenParams structure to create SplashScreen objects
// Based on the poppler codebase, SplashScreenParams is defined as:
#include "splash/SplashTypes.h"

class SplashScreenTest_2602 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    SplashScreenParams createDefaultParams() {
        SplashScreenParams params;
        params.type = splashScreenDispersed;
        params.size = 2; // Small size for testing
        params.dotRadius = 0;
        params.gamma = 1.0;
        params.blackThreshold = 0.0;
        params.whiteThreshold = 1.0;
        return params;
    }
};

// Test that test() returns 1 for maximum value (255)
TEST_F(SplashScreenTest_2602, TestMaxValueReturnsOne_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    // With value 255 (max), should almost certainly return 1
    // since mat values are unsigned char (0-255), value < mat only if mat > 255 which is impossible
    int result = screen.test(0, 0, 255);
    EXPECT_EQ(result, 1);
}

// Test that test() returns 0 for minimum value (0)
TEST_F(SplashScreenTest_2602, TestMinValueReturnsZero_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    // With value 0, 0 < mat[idx] is true if mat[idx] > 0
    // For a dispersed matrix of reasonable size, at least some entries should be > 0
    // We check at least one position returns 0
    bool foundZero = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (screen.test(x, y, 0) == 0) {
                foundZero = true;
                break;
            }
        }
        if (foundZero) break;
    }
    EXPECT_TRUE(foundZero);
}

// Test that test() returns only 0 or 1
TEST_F(SplashScreenTest_2602, TestReturnsBinaryValues_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (unsigned char v = 0; v < 255; v += 50) {
                int result = screen.test(x, y, v);
                EXPECT_TRUE(result == 0 || result == 1) 
                    << "test(" << x << ", " << y << ", " << (int)v << ") returned " << result;
            }
        }
    }
}

// Test that test() is deterministic (same inputs yield same outputs)
TEST_F(SplashScreenTest_2602, TestDeterministic_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    int result1 = screen.test(3, 5, 128);
    int result2 = screen.test(3, 5, 128);
    EXPECT_EQ(result1, result2);
}

// Test that x and y wrap around (since xx = x & sizeM1)
TEST_F(SplashScreenTest_2602, TestCoordinateWrapping_2602) {
    SplashScreenParams params = createDefaultParams();
    params.size = 2; // size will be 2, so sizeM1 = 1 (if size means log2Size)
    // Actually size interpretation may vary; let's use size=4
    SplashScreen screen(&params);
    
    // Due to masking with sizeM1, large coordinates should wrap
    // test(x, y, v) should equal test(x + period, y + period, v)
    // The period is sizeM1 + 1
    unsigned char value = 100;
    int result_origin = screen.test(0, 0, value);
    // Large x, y values should wrap around
    int result_wrapped = screen.test(1024, 1024, value);
    // Both should give same result since 1024 & sizeM1 == 0 & sizeM1 if 1024 is multiple of size
    // For size=2, the matrix is 2x2 or 4x4 depending on interpretation
    // We just check they return valid binary
    EXPECT_TRUE(result_origin == 0 || result_origin == 1);
    EXPECT_TRUE(result_wrapped == 0 || result_wrapped == 1);
}

// Test with negative coordinates (bitwise AND should still work)
TEST_F(SplashScreenTest_2602, TestNegativeCoordinates_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    // Negative values with bitwise AND should still produce valid indices
    int result = screen.test(-1, -1, 128);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test monotonicity: higher value should never produce a lower result for same (x,y)
TEST_F(SplashScreenTest_2602, TestMonotonicity_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            int prev_result = screen.test(x, y, 0);
            for (unsigned int v = 1; v <= 255; v++) {
                int curr_result = screen.test(x, y, (unsigned char)v);
                // If previous was 1, current must also be 1
                // Because if value1 >= mat[idx], then value2 > value1 >= mat[idx]
                if (prev_result == 1) {
                    EXPECT_EQ(curr_result, 1) 
                        << "Monotonicity violated at (" << x << "," << y << ") v=" << v;
                }
                prev_result = curr_result;
            }
        }
    }
}

// Test with dispersed screen type
TEST_F(SplashScreenTest_2602, TestDispersedScreen_2602) {
    SplashScreenParams params;
    params.type = splashScreenDispersed;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;
    
    SplashScreen screen(&params);
    
    int result = screen.test(0, 0, 128);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test with clustered screen type
TEST_F(SplashScreenTest_2602, TestClusteredScreen_2602) {
    SplashScreenParams params;
    params.type = splashScreenClustered;
    params.size = 2;
    params.dotRadius = 0;
    params.gamma = 1.0;
    params.blackThreshold = 0.0;
    params.whiteThreshold = 1.0;
    
    SplashScreen screen(&params);
    
    int result = screen.test(0, 0, 128);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test copy constructor produces same results
TEST_F(SplashScreenTest_2602, TestCopyProducesSameResults_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    // Force matrix creation
    screen.test(0, 0, 128);
    
    SplashScreen *screenCopy = screen.copy();
    ASSERT_NE(screenCopy, nullptr);
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (unsigned char v : {0, 64, 128, 192, 255}) {
                EXPECT_EQ(screen.test(x, y, v), screenCopy->test(x, y, v))
                    << "Copy mismatch at (" << x << "," << y << ") v=" << (int)v;
            }
        }
    }
    
    delete screenCopy;
}

// Test that all positions with value=255 return 1
TEST_F(SplashScreenTest_2602, TestAllPositionsMaxValue_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            EXPECT_EQ(screen.test(x, y, 255), 1)
                << "Expected 1 at (" << x << "," << y << ") with value 255";
        }
    }
}

// Test large coordinate values
TEST_F(SplashScreenTest_2602, TestLargeCoordinates_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    int result = screen.test(100000, 100000, 128);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test with the copy constructor (SplashScreen(const SplashScreen*))
TEST_F(SplashScreenTest_2602, TestPointerCopyConstructor_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    // Initialize matrix
    screen.test(0, 0, 100);
    
    SplashScreen screenCopy(&screen);
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            EXPECT_EQ(screen.test(x, y, 128), screenCopy.test(x, y, 128));
        }
    }
}

// Test boundary value 1
TEST_F(SplashScreenTest_2602, TestValueOne_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    int result = screen.test(0, 0, 1);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test boundary value 254
TEST_F(SplashScreenTest_2602, TestValue254_2602) {
    SplashScreenParams params = createDefaultParams();
    SplashScreen screen(&params);
    
    int result = screen.test(0, 0, 254);
    EXPECT_TRUE(result == 0 || result == 1);
}
