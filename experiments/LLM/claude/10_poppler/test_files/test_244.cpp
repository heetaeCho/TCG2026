#include <gtest/gtest.h>
#include "Stream.h"

class SplashBitmapCMYKEncoderTest_244 : public ::testing::Test {
protected:
    SplashBitmapCMYKEncoder encoder;
};

// Test that isBinary returns true when called with true
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinaryReturnsTrueWithTrueArg_244) {
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test that isBinary returns true when called with false
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinaryReturnsTrueWithFalseArg_244) {
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test that isBinary returns true with default-like argument (true, simulating "last")
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinaryAlwaysReturnsTrue_244) {
    // The parameter is ignored per the interface (commented out parameter name)
    // so the result should always be true regardless of the argument
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test that multiple calls consistently return true
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinaryConsistentAcrossMultipleCalls_244) {
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(encoder.isBinary(i % 2 == 0));
    }
}

// Test that a default-constructed encoder works correctly
TEST_F(SplashBitmapCMYKEncoderTest_244, DefaultConstructedEncoderIsBinary_244) {
    SplashBitmapCMYKEncoder freshEncoder;
    EXPECT_TRUE(freshEncoder.isBinary(true));
    EXPECT_TRUE(freshEncoder.isBinary(false));
}

// Test copy behavior - a copied encoder should also return true
TEST_F(SplashBitmapCMYKEncoderTest_244, CopiedEncoderIsBinary_244) {
    SplashBitmapCMYKEncoder copiedEncoder(encoder);
    EXPECT_TRUE(copiedEncoder.isBinary(true));
    EXPECT_TRUE(copiedEncoder.isBinary(false));
}
