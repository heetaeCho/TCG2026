#include <gtest/gtest.h>

// Include the header for the class under test
#include "FlateEncoder.h"

// Test that isBinary returns true with default parameter
TEST(FlateEncoderTest_1653, IsBinaryDefaultParam_1653) {
    FlateEncoder encoder;
    EXPECT_TRUE(encoder.isBinary());
}

// Test that isBinary returns true when explicitly passed true
TEST(FlateEncoderTest_1653, IsBinaryWithTrue_1653) {
    FlateEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test that isBinary returns true when explicitly passed false
TEST(FlateEncoderTest_1653, IsBinaryWithFalse_1653) {
    FlateEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test that isBinary is consistent across multiple calls
TEST(FlateEncoderTest_1653, IsBinaryConsistentAcrossCalls_1653) {
    FlateEncoder encoder;
    EXPECT_TRUE(encoder.isBinary());
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
    EXPECT_TRUE(encoder.isBinary());
}

// Test with multiple instances
TEST(FlateEncoderTest_1653, MultipleInstances_1653) {
    FlateEncoder encoder1;
    FlateEncoder encoder2;
    EXPECT_TRUE(encoder1.isBinary());
    EXPECT_TRUE(encoder2.isBinary());
    EXPECT_TRUE(encoder1.isBinary(false));
    EXPECT_TRUE(encoder2.isBinary(true));
}
