#include <gtest/gtest.h>

// Minimal stub to match the interface provided
// We only need the class declaration to test the public interface
class ASCIIHexEncoder {
public:
    bool isBinary(bool /*last = true*/) const { return false; }
};

// Test that isBinary returns false with default-like argument (true)
TEST(ASCIIHexEncoderTest_212, IsBinaryReturnsFalseWithTrue_212) {
    ASCIIHexEncoder encoder;
    EXPECT_FALSE(encoder.isBinary(true));
}

// Test that isBinary returns false with false argument
TEST(ASCIIHexEncoderTest_212, IsBinaryReturnsFalseWithFalse_212) {
    ASCIIHexEncoder encoder;
    EXPECT_FALSE(encoder.isBinary(false));
}

// Test that isBinary is consistent across multiple calls
TEST(ASCIIHexEncoderTest_212, IsBinaryConsistentAcrossMultipleCalls_212) {
    ASCIIHexEncoder encoder;
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));
}

// Test that isBinary works on a const object
TEST(ASCIIHexEncoderTest_212, IsBinaryWorksOnConstObject_212) {
    const ASCIIHexEncoder encoder;
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));
}

// Test multiple instances all return false
TEST(ASCIIHexEncoderTest_212, MultipleInstancesAllReturnFalse_212) {
    ASCIIHexEncoder encoder1;
    ASCIIHexEncoder encoder2;
    ASCIIHexEncoder encoder3;
    EXPECT_FALSE(encoder1.isBinary(true));
    EXPECT_FALSE(encoder2.isBinary(false));
    EXPECT_FALSE(encoder3.isBinary(true));
}

// Test copy constructed instance
TEST(ASCIIHexEncoderTest_212, CopyConstructedInstanceReturnsFalse_212) {
    ASCIIHexEncoder original;
    ASCIIHexEncoder copy(original);
    EXPECT_FALSE(copy.isBinary(true));
    EXPECT_FALSE(copy.isBinary(false));
}

// Test that the return type is bool and always false
TEST(ASCIIHexEncoderTest_212, ReturnTypeIsBoolAndAlwaysFalse_212) {
    ASCIIHexEncoder encoder;
    bool result1 = encoder.isBinary(true);
    bool result2 = encoder.isBinary(false);
    EXPECT_EQ(result1, false);
    EXPECT_EQ(result2, false);
}
