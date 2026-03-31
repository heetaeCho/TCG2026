#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Declare the function under test
namespace Exiv2 {
namespace Internal {
std::string upper(std::string_view str);
}
}

using Exiv2::Internal::upper;

// Normal operation tests

TEST(UpperTest_1271, LowercaseString_1271) {
    std::string result = upper("hello");
    EXPECT_EQ(result, "HELLO");
}

TEST(UpperTest_1271, UppercaseString_1271) {
    std::string result = upper("HELLO");
    EXPECT_EQ(result, "HELLO");
}

TEST(UpperTest_1271, MixedCaseString_1271) {
    std::string result = upper("HeLLo WoRLd");
    EXPECT_EQ(result, "HELLO WORLD");
}

TEST(UpperTest_1271, EmptyString_1271) {
    std::string result = upper("");
    EXPECT_EQ(result, "");
}

TEST(UpperTest_1271, SingleLowercaseChar_1271) {
    std::string result = upper("a");
    EXPECT_EQ(result, "A");
}

TEST(UpperTest_1271, SingleUppercaseChar_1271) {
    std::string result = upper("Z");
    EXPECT_EQ(result, "Z");
}

// Boundary conditions

TEST(UpperTest_1271, DigitsUnchanged_1271) {
    std::string result = upper("12345");
    EXPECT_EQ(result, "12345");
}

TEST(UpperTest_1271, SpecialCharactersUnchanged_1271) {
    std::string result = upper("!@#$%^&*()");
    EXPECT_EQ(result, "!@#$%^&*()");
}

TEST(UpperTest_1271, MixedAlphaNumericSpecial_1271) {
    std::string result = upper("abc123!DEF");
    EXPECT_EQ(result, "ABC123!DEF");
}

TEST(UpperTest_1271, WhitespaceOnly_1271) {
    std::string result = upper("   ");
    EXPECT_EQ(result, "   ");
}

TEST(UpperTest_1271, TabsAndNewlines_1271) {
    std::string result = upper("hello\tworld\n");
    EXPECT_EQ(result, "HELLO\tWORLD\n");
}

TEST(UpperTest_1271, AllLowercaseAlphabet_1271) {
    std::string result = upper("abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(UpperTest_1271, AllUppercaseAlphabet_1271) {
    std::string result = upper("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(UpperTest_1271, NullCharInMiddle_1271) {
    std::string_view sv("ab\0cd", 5);
    std::string result = upper(sv);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], 'B');
    EXPECT_EQ(result[2], '\0');
    EXPECT_EQ(result[3], 'C');
    EXPECT_EQ(result[4], 'D');
}

TEST(UpperTest_1271, HighAsciiCharacters_1271) {
    // Characters with values > 127 should not cause undefined behavior
    std::string input;
    input.push_back(static_cast<char>(200));
    input.push_back(static_cast<char>(255));
    input.push_back('a');
    std::string result = upper(input);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[2], 'A');
}

TEST(UpperTest_1271, LongString_1271) {
    std::string input(1000, 'a');
    std::string expected(1000, 'A');
    std::string result = upper(input);
    EXPECT_EQ(result, expected);
}

TEST(UpperTest_1271, StringViewFromSubstring_1271) {
    std::string full = "xxhelloxx";
    std::string_view sv(full.data() + 2, 5);
    std::string result = upper(sv);
    EXPECT_EQ(result, "HELLO");
}

TEST(UpperTest_1271, PreservesLength_1271) {
    std::string input = "Test String 123";
    std::string result = upper(input);
    EXPECT_EQ(result.size(), input.size());
}
