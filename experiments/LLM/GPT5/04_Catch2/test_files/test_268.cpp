// File: tests/stringmaker_byte_convert_test.cpp

#include <gtest/gtest.h>
#include <string>
#include <cstddef>     // std::byte, std::to_integer
#include "catch2/catch_tostring.hpp"  // Declaration of StringMaker

using Catch::StringMaker;

class StringMakerByteTest_268 : public ::testing::Test {};

// Normal operation: basic values
TEST_F(StringMakerByteTest_268, ConvertsZeroToDecimalString_268) {
    const std::byte b = static_cast<std::byte>(0);
    const std::string s = StringMaker<std::byte>::convert(b);
    EXPECT_EQ(s, "0");
}

TEST_F(StringMakerByteTest_268, ConvertsSmallValueToDecimalString_268) {
    const unsigned val = 10u;
    const std::byte b = static_cast<std::byte>(val);
    const std::string s = StringMaker<std::byte>::convert(b);
    // Expect plain decimal digits without extra formatting
    EXPECT_EQ(s, std::to_string(val));
}

// Boundary conditions: extremes in the byte range
TEST_F(StringMakerByteTest_268, ConvertsMaxByteToDecimalString_268) {
    const unsigned val = 255u;  // max for a byte
    const std::byte b = static_cast<std::byte>(val);
    const std::string s = StringMaker<std::byte>::convert(b);
    EXPECT_EQ(s, std::to_string(val));
}

TEST_F(StringMakerByteTest_268, ConvertsMidRangeByteToDecimalString_268) {
    const unsigned val = 127u;  // typical mid-range
    const std::byte b = static_cast<std::byte>(val);
    const std::string s = StringMaker<std::byte>::convert(b);
    EXPECT_EQ(s, std::to_string(val));
}

// Exceptional/edge-like observable behaviors:
// Ensure the output is numeric rather than character/hex-like formatting.
TEST_F(StringMakerByteTest_268, DoesNotUseCharacterFormatting_268) {
    const unsigned val = 65u;  // 'A' in ASCII
    const std::byte b = static_cast<std::byte>(val);
    const std::string s = StringMaker<std::byte>::convert(b);

    // Should be "65", not "A"
    EXPECT_EQ(s, "65");
    EXPECT_NE(s, "A");
}

TEST_F(StringMakerByteTest_268, DoesNotUseHexPrefixOrNotation_268) {
    const unsigned val = 255u;
    const std::byte b = static_cast<std::byte>(val);
    const std::string s = StringMaker<std::byte>::convert(b);

    // Expect decimal without hex markers
    EXPECT_EQ(s, "255");
    EXPECT_NE(s, "0xff");
    EXPECT_NE(s, "FF");
}

// Cross-check using observable standard conversion
TEST_F(StringMakerByteTest_268, MatchesStdToIntegerThenToString_268) {
    for (unsigned val : {0u, 1u, 2u, 10u, 42u, 127u, 128u, 200u, 254u, 255u}) {
        const std::byte b = static_cast<std::byte>(val);
        const std::string expected = std::to_string(std::to_integer<unsigned long long>(b));
        const std::string actual   = StringMaker<std::byte>::convert(b);
        EXPECT_EQ(actual, expected) << "Mismatch for value " << val;
    }
}
