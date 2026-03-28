#include <gtest/gtest.h>
#include <string>
#include <climits>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

// Test fixture for StringMaker<unsigned long> tests
class StringMakerUnsignedLongTest_273 : public ::testing::Test {
protected:
    // Helper to convert and return the string
    std::string convert(unsigned long value) {
        return Catch::StringMaker<unsigned long>::convert(value);
    }
};

// Normal operation: converting zero
TEST_F(StringMakerUnsignedLongTest_273, ConvertZero_273) {
    std::string result = convert(0UL);
    EXPECT_EQ(result, "0");
}

// Normal operation: converting a small positive value
TEST_F(StringMakerUnsignedLongTest_273, ConvertSmallPositiveValue_273) {
    std::string result = convert(42UL);
    EXPECT_EQ(result, "42");
}

// Normal operation: converting one
TEST_F(StringMakerUnsignedLongTest_273, ConvertOne_273) {
    std::string result = convert(1UL);
    EXPECT_EQ(result, "1");
}

// Normal operation: converting a typical value
TEST_F(StringMakerUnsignedLongTest_273, ConvertTypicalValue_273) {
    std::string result = convert(123456789UL);
    EXPECT_EQ(result, "123456789");
}

// Boundary condition: converting ULONG_MAX
TEST_F(StringMakerUnsignedLongTest_273, ConvertMaxValue_273) {
    unsigned long maxVal = ULONG_MAX;
    std::string result = convert(maxVal);
    // ULONG_MAX should produce a valid numeric string
    std::string expected = std::to_string(maxVal);
    EXPECT_EQ(result, expected);
}

// Boundary condition: converting a large value just below max
TEST_F(StringMakerUnsignedLongTest_273, ConvertLargeValue_273) {
    unsigned long val = ULONG_MAX - 1;
    std::string result = convert(val);
    std::string expected = std::to_string(val);
    EXPECT_EQ(result, expected);
}

// Normal operation: converting a power of two
TEST_F(StringMakerUnsignedLongTest_273, ConvertPowerOfTwo_273) {
    std::string result = convert(1024UL);
    EXPECT_EQ(result, "1024");
}

// Normal operation: converting 1000
TEST_F(StringMakerUnsignedLongTest_273, ConvertThousand_273) {
    std::string result = convert(1000UL);
    EXPECT_EQ(result, "1000");
}

// Normal operation: converting 10
TEST_F(StringMakerUnsignedLongTest_273, ConvertTen_273) {
    std::string result = convert(10UL);
    EXPECT_EQ(result, "10");
}

// Verify the result is not empty for any valid input
TEST_F(StringMakerUnsignedLongTest_273, ResultIsNonEmpty_273) {
    EXPECT_FALSE(convert(0UL).empty());
    EXPECT_FALSE(convert(1UL).empty());
    EXPECT_FALSE(convert(ULONG_MAX).empty());
}

// Verify that different values produce different strings
TEST_F(StringMakerUnsignedLongTest_273, DifferentValuesProduceDifferentStrings_273) {
    std::string result0 = convert(0UL);
    std::string result1 = convert(1UL);
    std::string result2 = convert(2UL);
    EXPECT_NE(result0, result1);
    EXPECT_NE(result1, result2);
    EXPECT_NE(result0, result2);
}

// Verify consistency: calling convert twice with the same value gives same result
TEST_F(StringMakerUnsignedLongTest_273, ConsistentResults_273) {
    unsigned long val = 999999UL;
    std::string result1 = convert(val);
    std::string result2 = convert(val);
    EXPECT_EQ(result1, result2);
}

// Boundary: value that fits in 32 bits on 64-bit systems
TEST_F(StringMakerUnsignedLongTest_273, ConvertUint32MaxEquivalent_273) {
    unsigned long val = 4294967295UL; // 2^32 - 1
    std::string result = convert(val);
    std::string expected = std::to_string(val);
    EXPECT_EQ(result, expected);
}

// Test with a round number
TEST_F(StringMakerUnsignedLongTest_273, ConvertMillion_273) {
    std::string result = convert(1000000UL);
    EXPECT_EQ(result, "1000000");
}
