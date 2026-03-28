#include <gtest/gtest.h>

// Include the header that contains LZWEncoder
#include "Stream.h"

// Test that isBinary returns true with default parameter
TEST(LZWEncoderTest_228, IsBinaryReturnsTrueDefault_228) {
    LZWEncoder encoder;
    EXPECT_TRUE(encoder.isBinary());
}

// Test that isBinary returns true when passed true
TEST(LZWEncoderTest_228, IsBinaryReturnsTrueWhenPassedTrue_228) {
    LZWEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test that isBinary returns true when passed false
TEST(LZWEncoderTest_228, IsBinaryReturnsTrueWhenPassedFalse_228) {
    LZWEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test that isBinary is consistent across multiple calls
TEST(LZWEncoderTest_228, IsBinaryConsistentAcrossMultipleCalls_228) {
    LZWEncoder encoder;
    EXPECT_TRUE(encoder.isBinary());
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
    EXPECT_TRUE(encoder.isBinary());
}

// Test that isBinary is const-correct (can be called on const object)
TEST(LZWEncoderTest_228, IsBinaryWorksOnConstObject_228) {
    const LZWEncoder encoder;
    EXPECT_TRUE(encoder.isBinary());
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test multiple instances return the same result
TEST(LZWEncoderTest_228, MultipleInstancesReturnTrue_228) {
    LZWEncoder encoder1;
    LZWEncoder encoder2;
    EXPECT_EQ(encoder1.isBinary(), encoder2.isBinary());
    EXPECT_TRUE(encoder1.isBinary());
    EXPECT_TRUE(encoder2.isBinary());
}
