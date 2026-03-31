#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280 : public ::testing::Test {
protected:
};

// Test with a proper Unicode BOM (FE FF) and even length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, ValidBOMAndEvenLength_1280) {
    // Unicode BOM is 0xFE 0xFF
    std::string s = {'\xFE', '\xFF', '\x00', '\x41'};
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with a proper Unicode BOM but odd length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, ValidBOMAndOddLength_1280) {
    std::string s = {'\xFE', '\xFF', '\x00'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with no BOM but even length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, NoBOMAndEvenLength_1280) {
    std::string s = {'\x00', '\x41', '\x00', '\x42'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with no BOM and odd length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, NoBOMAndOddLength_1280) {
    std::string s = {'\x00', '\x41', '\x00'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with empty string
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, EmptyString_1280) {
    std::string s;
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with just the BOM (2 bytes, even length)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, JustBOM_1280) {
    std::string s = {'\xFE', '\xFF'};
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with single byte
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, SingleByte_1280) {
    std::string s = {'\xFE'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with BOM followed by multiple even-length content
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMWithLongerEvenContent_1280) {
    std::string s = {'\xFE', '\xFF', '\x00', '\x41', '\x00', '\x42', '\x00', '\x43'};
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with BOM followed by multiple chars making total odd
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMWithLongerOddContent_1280) {
    std::string s = {'\xFE', '\xFF', '\x00', '\x41', '\x00', '\x42', '\x00'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with reversed BOM (Little Endian BOM: FF FE) - should not match UTF-16 BE BOM
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, ReversedBOMEvenLength_1280) {
    std::string s = {'\xFF', '\xFE', '\x00', '\x41'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with BOM-like bytes but only first byte matches
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, PartialBOMFirstByteOnly_1280) {
    std::string s = {'\xFE', '\x00', '\x00', '\x41'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with BOM and embedded null characters
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMWithNullCharacters_1280) {
    std::string s = {'\xFE', '\xFF', '\x00', '\x00'};
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with string containing BOM in the middle (not at start)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMInMiddle_1280) {
    std::string s = {'\x00', '\x41', '\xFE', '\xFF'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with a 6-byte string with BOM (even)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMWith6BytesEven_1280) {
    std::string s = {'\xFE', '\xFF', '\x00', '\x48', '\x00', '\x69'};
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test with a 5-byte string with BOM (odd)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, BOMWith5BytesOdd_1280) {
    std::string s = {'\xFE', '\xFF', '\x00', '\x48', '\x00'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}

// Test string_view from a larger buffer
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, StringViewSubset_1280) {
    std::string fullString = {'\xFE', '\xFF', '\x00', '\x41', '\x00', '\x42'};
    std::string_view sv(fullString.data(), 4); // Even length with BOM
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Test string_view of odd length from larger buffer
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, StringViewOddSubset_1280) {
    std::string fullString = {'\xFE', '\xFF', '\x00', '\x41', '\x00', '\x42'};
    std::string_view sv(fullString.data(), 3);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Test with two-byte string that is not BOM
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1280, TwoBytesNoBOM_1280) {
    std::string s = {'\x41', '\x42'};
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(s));
}
