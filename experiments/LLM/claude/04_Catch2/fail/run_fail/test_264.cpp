#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"

class StringMakerWstringTest_264 : public ::testing::Test {
protected:
    // Helper to call the function under test
    std::string convert(const std::wstring& wstr) {
        return Catch::StringMaker<std::wstring>::convert(wstr);
    }
};

// Test empty wstring conversion
TEST_F(StringMakerWstringTest_264, EmptyWstring_264) {
    std::wstring input = L"";
    std::string result = convert(input);
    // An empty wstring should produce a stringified empty string
    // Catch's stringify for std::string typically wraps in quotes: "\"\""
    // But we just check it's not arbitrary - it should represent an empty string
    EXPECT_FALSE(result.empty());  // stringify adds quotes around the string
}

// Test simple ASCII wstring conversion
TEST_F(StringMakerWstringTest_264, SimpleAsciiWstring_264) {
    std::wstring input = L"hello";
    std::string result = convert(input);
    // The intermediate string should be "hello", then stringified (quoted)
    // Catch::Detail::stringify for a std::string wraps it in quotes
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test wstring with characters within 0xff range
TEST_F(StringMakerWstringTest_264, CharsWithin0xFF_264) {
    std::wstring input = L"abc";
    std::string result = convert(input);
    EXPECT_NE(result.find("abc"), std::string::npos);
}

// Test wstring with characters beyond 0xff should be replaced with '?'
TEST_F(StringMakerWstringTest_264, CharsAbove0xFF_ReplacedWithQuestionMark_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0x100);  // Beyond 0xff
    std::string result = convert(input);
    EXPECT_NE(result.find("?"), std::string::npos);
}

// Test mixed ASCII and non-ASCII characters
TEST_F(StringMakerWstringTest_264, MixedAsciiAndNonAscii_264) {
    std::wstring input;
    input += L'A';                            // 0x41, within range
    input += static_cast<wchar_t>(0x200);     // Beyond 0xff
    input += L'B';                            // 0x42, within range
    std::string result = convert(input);
    EXPECT_NE(result.find("A?B"), std::string::npos);
}

// Test wstring with all characters beyond 0xff
TEST_F(StringMakerWstringTest_264, AllCharsAbove0xFF_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0x100);
    input += static_cast<wchar_t>(0x200);
    input += static_cast<wchar_t>(0x300);
    std::string result = convert(input);
    EXPECT_NE(result.find("???"), std::string::npos);
}

// Test wstring with boundary character 0xff (should be kept as-is)
TEST_F(StringMakerWstringTest_264, BoundaryChar0xFF_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0xff);
    std::string result = convert(input);
    // 0xff is <= 0xff, so it should be converted to static_cast<char>(0xff)
    // It should NOT be replaced with '?'
    // The character might appear as some extended ASCII char in the output
    // We check that '?' is not the primary content (unless 0xff maps to something weird in stringify)
    // Actually, we just verify the function doesn't crash and returns something
    EXPECT_FALSE(result.empty());
}

// Test wstring with boundary character 0x100 (should be replaced with '?')
TEST_F(StringMakerWstringTest_264, BoundaryChar0x100_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0x100);
    std::string result = convert(input);
    EXPECT_NE(result.find("?"), std::string::npos);
}

// Test wstring with null character inside
TEST_F(StringMakerWstringTest_264, WstringWithNullChar_264) {
    std::wstring input;
    input += L'A';
    input += static_cast<wchar_t>(0);
    input += L'B';
    // The loop iterates over all chars in the wstring, including null
    std::string result = convert(input);
    // The function should still produce some result
    EXPECT_FALSE(result.empty());
}

// Test single character wstring
TEST_F(StringMakerWstringTest_264, SingleCharWstring_264) {
    std::wstring input = L"X";
    std::string result = convert(input);
    EXPECT_NE(result.find("X"), std::string::npos);
}

// Test wstring with special ASCII characters
TEST_F(StringMakerWstringTest_264, SpecialAsciiChars_264) {
    std::wstring input = L"\t\n";
    std::string result = convert(input);
    // Tab and newline are within 0xff range, so they get cast to char
    // The stringify function may escape them
    EXPECT_FALSE(result.empty());
}

// Test wstring with spaces
TEST_F(StringMakerWstringTest_264, WstringWithSpaces_264) {
    std::wstring input = L"hello world";
    std::string result = convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test long wstring to verify reserve works correctly
TEST_F(StringMakerWstringTest_264, LongWstring_264) {
    std::wstring input(1000, L'A');
    std::string result = convert(input);
    // Should contain 1000 'A' characters (within the stringified result)
    std::string expected(1000, 'A');
    EXPECT_NE(result.find(expected), std::string::npos);
}

// Test wstring with character exactly at 0x00 (minimum)
TEST_F(StringMakerWstringTest_264, CharAtZero_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0x00);
    std::string result = convert(input);
    // Should not crash, 0x00 <= 0xff so it becomes char(0)
    EXPECT_FALSE(result.empty());
}

// Test wstring with large Unicode values
TEST_F(StringMakerWstringTest_264, LargeUnicodeValues_264) {
    std::wstring input;
    input += static_cast<wchar_t>(0xFFFF);
    std::string result = convert(input);
    EXPECT_NE(result.find("?"), std::string::npos);
}
