#include <gtest/gtest.h>
#include "Stream.h"

// Test that isBinary returns true with default-like argument
TEST(RunLengthEncoderTest_224, IsBinaryReturnsTrue_224) {
    RunLengthEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test that isBinary returns true when passed false
TEST(RunLengthEncoderTest_224, IsBinaryReturnsTrueWithFalseArg_224) {
    RunLengthEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test that isBinary consistently returns true on multiple calls
TEST(RunLengthEncoderTest_224, IsBinaryConsistentlyReturnsTrue_224) {
    RunLengthEncoder encoder;
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test that multiple instances all return true for isBinary
TEST(RunLengthEncoderTest_224, MultipleInstancesReturnTrue_224) {
    RunLengthEncoder encoder1;
    RunLengthEncoder encoder2;
    EXPECT_TRUE(encoder1.isBinary(true));
    EXPECT_TRUE(encoder2.isBinary(false));
}
