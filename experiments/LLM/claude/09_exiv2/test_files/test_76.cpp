#include <gtest/gtest.h>
#include <string_view>
#include "utils.hpp"

using namespace Exiv2::Internal;

// Tests for contains(std::string_view, char)

TEST(ContainsTest_76, CharFoundAtBeginning_76) {
    EXPECT_TRUE(contains("hello", 'h'));
}

TEST(ContainsTest_76, CharFoundAtEnd_76) {
    EXPECT_TRUE(contains("hello", 'o'));
}

TEST(ContainsTest_76, CharFoundInMiddle_76) {
    EXPECT_TRUE(contains("hello", 'l'));
}

TEST(ContainsTest_76, CharNotFound_76) {
    EXPECT_FALSE(contains("hello", 'z'));
}

TEST(ContainsTest_76, EmptyStringCharNotFound_76) {
    EXPECT_FALSE(contains("", 'a'));
}

TEST(ContainsTest_76, SingleCharStringFound_76) {
    EXPECT_TRUE(contains("a", 'a'));
}

TEST(ContainsTest_76, SingleCharStringNotFound_76) {
    EXPECT_FALSE(contains("a", 'b'));
}

TEST(ContainsTest_76, NullCharInString_76) {
    std::string_view sv("hel\0lo", 6);
    EXPECT_TRUE(contains(sv, '\0'));
}

TEST(ContainsTest_76, NullCharNotInString_76) {
    EXPECT_FALSE(contains("hello", '\0'));
}

TEST(ContainsTest_76, SpaceCharFound_76) {
    EXPECT_TRUE(contains("hello world", ' '));
}

TEST(ContainsTest_76, SpaceCharNotFound_76) {
    EXPECT_FALSE(contains("helloworld", ' '));
}

TEST(ContainsTest_76, SpecialCharFound_76) {
    EXPECT_TRUE(contains("path/to/file.ext", '/'));
}

TEST(ContainsTest_76, SpecialCharNotFound_76) {
    EXPECT_FALSE(contains("path_to_file", '/'));
}

TEST(ContainsTest_76, DotCharFound_76) {
    EXPECT_TRUE(contains("file.jpg", '.'));
}

TEST(ContainsTest_76, DotCharNotFound_76) {
    EXPECT_FALSE(contains("filejpg", '.'));
}

TEST(ContainsTest_76, NewlineCharFound_76) {
    EXPECT_TRUE(contains("line1\nline2", '\n'));
}

TEST(ContainsTest_76, NewlineCharNotFound_76) {
    EXPECT_FALSE(contains("line1line2", '\n'));
}

TEST(ContainsTest_76, TabCharFound_76) {
    EXPECT_TRUE(contains("col1\tcol2", '\t'));
}

TEST(ContainsTest_76, RepeatedCharFound_76) {
    EXPECT_TRUE(contains("aaaa", 'a'));
}

TEST(ContainsTest_76, NumericCharFound_76) {
    EXPECT_TRUE(contains("abc123", '1'));
}

TEST(ContainsTest_76, NumericCharNotFound_76) {
    EXPECT_FALSE(contains("abcdef", '1'));
}

// Tests for contains(std::string_view, std::string_view) — if supported

TEST(ContainsStringViewTest_76, SubstringFound_76) {
    EXPECT_TRUE(contains("hello world", "world"));
}

TEST(ContainsStringViewTest_76, SubstringNotFound_76) {
    EXPECT_FALSE(contains("hello world", "xyz"));
}

TEST(ContainsStringViewTest_76, EmptySubstringAlwaysFound_76) {
    EXPECT_TRUE(contains("hello", ""));
}

TEST(ContainsStringViewTest_76, EmptyStringEmptySubstring_76) {
    EXPECT_TRUE(contains("", ""));
}

TEST(ContainsStringViewTest_76, EmptyStringNonEmptySubstring_76) {
    EXPECT_FALSE(contains("", "abc"));
}

TEST(ContainsStringViewTest_76, ExactMatch_76) {
    EXPECT_TRUE(contains("hello", "hello"));
}

TEST(ContainsStringViewTest_76, SubstringAtBeginning_76) {
    EXPECT_TRUE(contains("hello world", "hello"));
}

TEST(ContainsStringViewTest_76, SubstringAtEnd_76) {
    EXPECT_TRUE(contains("hello world", "world"));
}

TEST(ContainsStringViewTest_76, SubstringLongerThanString_76) {
    EXPECT_FALSE(contains("hi", "hello"));
}

TEST(ContainsStringViewTest_76, SingleCharSubstringFound_76) {
    EXPECT_TRUE(contains("hello", "e"));
}

TEST(ContainsStringViewTest_76, SingleCharSubstringNotFound_76) {
    EXPECT_FALSE(contains("hello", "z"));
}

TEST(ContainsStringViewTest_76, PartialOverlapNotFound_76) {
    EXPECT_FALSE(contains("abcde", "abcdef"));
}

TEST(ContainsStringViewTest_76, RepeatedPatternFound_76) {
    EXPECT_TRUE(contains("ababab", "bab"));
}
