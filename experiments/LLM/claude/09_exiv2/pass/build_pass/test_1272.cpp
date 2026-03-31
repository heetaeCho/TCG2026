#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Declare the function under test
namespace Exiv2 {
namespace Internal {
std::string lower(std::string_view a);
}
}

using Exiv2::Internal::lower;

// Normal operation tests

TEST(LowerTest_1272, EmptyString_1272) {
    std::string result = lower("");
    EXPECT_EQ(result, "");
}

TEST(LowerTest_1272, AllLowercase_1272) {
    std::string result = lower("hello");
    EXPECT_EQ(result, "hello");
}

TEST(LowerTest_1272, AllUppercase_1272) {
    std::string result = lower("HELLO");
    EXPECT_EQ(result, "hello");
}

TEST(LowerTest_1272, MixedCase_1272) {
    std::string result = lower("HeLLo WoRLd");
    EXPECT_EQ(result, "hello world");
}

TEST(LowerTest_1272, SingleUppercaseChar_1272) {
    std::string result = lower("A");
    EXPECT_EQ(result, "a");
}

TEST(LowerTest_1272, SingleLowercaseChar_1272) {
    std::string result = lower("a");
    EXPECT_EQ(result, "a");
}

TEST(LowerTest_1272, NumericString_1272) {
    std::string result = lower("12345");
    EXPECT_EQ(result, "12345");
}

TEST(LowerTest_1272, MixedAlphanumeric_1272) {
    std::string result = lower("Hello123World");
    EXPECT_EQ(result, "hello123world");
}

TEST(LowerTest_1272, SpecialCharacters_1272) {
    std::string result = lower("!@#$%^&*()");
    EXPECT_EQ(result, "!@#$%^&*()");
}

TEST(LowerTest_1272, WhitespaceOnly_1272) {
    std::string result = lower("   \t\n");
    EXPECT_EQ(result, "   \t\n");
}

TEST(LowerTest_1272, MixedWithSpecialChars_1272) {
    std::string result = lower("Hello, World! 123");
    EXPECT_EQ(result, "hello, world! 123");
}

// Boundary conditions

TEST(LowerTest_1272, AllZCharacters_1272) {
    std::string result = lower("Z");
    EXPECT_EQ(result, "z");
}

TEST(LowerTest_1272, AllACharacters_1272) {
    std::string result = lower("A");
    EXPECT_EQ(result, "a");
}

TEST(LowerTest_1272, FullAlphabetUpper_1272) {
    std::string result = lower("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

TEST(LowerTest_1272, FullAlphabetLower_1272) {
    std::string result = lower("abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

TEST(LowerTest_1272, HighAsciiChars_1272) {
    // Characters with values > 127 should pass through without issue
    std::string input;
    input.push_back(static_cast<char>(200));
    input.push_back(static_cast<char>(255));
    input.push_back(static_cast<char>(128));
    std::string result = lower(input);
    // These are not uppercase ASCII letters, so they should remain unchanged
    // (behavior depends on locale, but with unsigned char cast, no UB)
    EXPECT_EQ(result.size(), 3u);
}

TEST(LowerTest_1272, NullCharacterInMiddle_1272) {
    // string_view can handle embedded null characters
    std::string_view input("AB\0CD", 5);
    std::string result = lower(input);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], 'b');
    EXPECT_EQ(result[2], '\0');
    EXPECT_EQ(result[3], 'c');
    EXPECT_EQ(result[4], 'd');
}

TEST(LowerTest_1272, LongString_1272) {
    std::string input(10000, 'X');
    std::string expected(10000, 'x');
    std::string result = lower(input);
    EXPECT_EQ(result, expected);
}

TEST(LowerTest_1272, PreservesLength_1272) {
    std::string input = "TestString";
    std::string result = lower(input);
    EXPECT_EQ(result.size(), input.size());
}

TEST(LowerTest_1272, TabsAndNewlines_1272) {
    std::string result = lower("HELLO\tWORLD\n");
    EXPECT_EQ(result, "hello\tworld\n");
}

TEST(LowerTest_1272, RepeatedSameChar_1272) {
    std::string result = lower("AAAA");
    EXPECT_EQ(result, "aaaa");
}

TEST(LowerTest_1272, StringViewFromSubstring_1272) {
    std::string full = "Hello World";
    std::string_view sv(full.data() + 6, 5); // "World"
    std::string result = lower(sv);
    EXPECT_EQ(result, "world");
}
