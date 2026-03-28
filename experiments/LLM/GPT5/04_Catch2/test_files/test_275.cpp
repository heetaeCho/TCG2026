// File: stringmaker_signed_char_convert_test_275.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"

// Convenience alias
using Catch::StringMaker;

class StringMakerSignedCharTest_275 : public ::testing::Test {};

// --- Special control characters ---

TEST_F(StringMakerSignedCharTest_275, ConvertsCarriageReturnToEscaped_275) {
    signed char v = '\r';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "'\\r'");
}

TEST_F(StringMakerSignedCharTest_275, ConvertsFormFeedToEscaped_275) {
    signed char v = '\f';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "'\\f'");
}

TEST_F(StringMakerSignedCharTest_275, ConvertsNewlineToEscaped_275) {
    signed char v = '\n';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "'\\n'");
}

TEST_F(StringMakerSignedCharTest_275, ConvertsTabToEscaped_275) {
    signed char v = '\t';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "'\\t'");
}

// --- Boundary and general printable characters ---

TEST_F(StringMakerSignedCharTest_275, ConvertsSpaceToQuotedSpace_275) {
    signed char v = ' ';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "' '");
}

TEST_F(StringMakerSignedCharTest_275, ConvertsPrintableLetterToQuoted_275) {
    signed char v = 'A';
    EXPECT_EQ(StringMaker<signed char>::convert(v), "'A'");
}

// --- Non-printable range that delegates to stringify(unsigned) ---

TEST_F(StringMakerSignedCharTest_275, ConvertsNULUsingUnsignedStringify_275) {
    signed char v = '\0'; // 0
    // Expectation is whatever Catch::Detail::stringify produces for unsigned int(0)
    std::string expected = ::Catch::Detail::stringify(static_cast<unsigned int>(v));
    EXPECT_EQ(StringMaker<signed char>::convert(v), expected);
}

TEST_F(StringMakerSignedCharTest_275, ConvertsUnitSeparatorUsingUnsignedStringify_275) {
    signed char v = 0x1F; // 31, still < ' '
    std::string expected = ::Catch::Detail::stringify(static_cast<unsigned int>(v));
    EXPECT_EQ(StringMaker<signed char>::convert(v), expected);
}

// --- Negative value handling (signed char below 0 should be quoted as-is) ---

TEST_F(StringMakerSignedCharTest_275, ConvertsNegativeSignedCharToQuotedByte_275) {
    signed char v = static_cast<signed char>(-1);
    // Build expected quoted string: "'<byte>'" where byte is v placed verbatim
    std::string expected = "' '";
    expected[1] = static_cast<char>(v);
    EXPECT_EQ(StringMaker<signed char>::convert(v), expected);
}
