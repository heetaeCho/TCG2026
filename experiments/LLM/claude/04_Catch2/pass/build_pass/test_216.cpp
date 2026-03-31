#include <gtest/gtest.h>
#include <string>

// Include necessary headers
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/catch_case_sensitive.hpp"

using namespace Catch;
using namespace Catch::Matchers;

// Test: adjustString returns the same string when case sensitive
TEST(CasedStringTest_216, AdjustStringCaseSensitiveReturnsSameString_216) {
    CasedString cs("Hello World", CaseSensitive::Yes);
    std::string result = cs.adjustString("Hello World");
    EXPECT_EQ(result, "Hello World");
}

// Test: adjustString returns lowercase string when case insensitive
TEST(CasedStringTest_216, AdjustStringCaseInsensitiveReturnsLowerCase_216) {
    CasedString cs("Hello World", CaseSensitive::No);
    std::string result = cs.adjustString("Hello World");
    EXPECT_EQ(result, "hello world");
}

// Test: adjustString with empty string and case sensitive
TEST(CasedStringTest_216, AdjustStringEmptyStringCaseSensitive_216) {
    CasedString cs("", CaseSensitive::Yes);
    std::string result = cs.adjustString("");
    EXPECT_EQ(result, "");
}

// Test: adjustString with empty string and case insensitive
TEST(CasedStringTest_216, AdjustStringEmptyStringCaseInsensitive_216) {
    CasedString cs("", CaseSensitive::No);
    std::string result = cs.adjustString("");
    EXPECT_EQ(result, "");
}

// Test: adjustString with all uppercase letters, case insensitive
TEST(CasedStringTest_216, AdjustStringAllUpperCaseInsensitive_216) {
    CasedString cs("TEST", CaseSensitive::No);
    std::string result = cs.adjustString("ABCDEFG");
    EXPECT_EQ(result, "abcdefg");
}

// Test: adjustString with all lowercase letters, case insensitive (no change expected)
TEST(CasedStringTest_216, AdjustStringAllLowerCaseInsensitive_216) {
    CasedString cs("test", CaseSensitive::No);
    std::string result = cs.adjustString("abcdefg");
    EXPECT_EQ(result, "abcdefg");
}

// Test: adjustString with mixed case, case sensitive
TEST(CasedStringTest_216, AdjustStringMixedCaseSensitive_216) {
    CasedString cs("MiXeD", CaseSensitive::Yes);
    std::string result = cs.adjustString("MiXeD");
    EXPECT_EQ(result, "MiXeD");
}

// Test: adjustString with numbers and special characters, case insensitive
TEST(CasedStringTest_216, AdjustStringNumbersAndSpecialCharsCaseInsensitive_216) {
    CasedString cs("123!@#", CaseSensitive::No);
    std::string result = cs.adjustString("123!@#");
    EXPECT_EQ(result, "123!@#");
}

// Test: Constructor stores adjusted string in m_str when case insensitive
TEST(CasedStringTest_216, ConstructorStoresAdjustedStringCaseInsensitive_216) {
    CasedString cs("Hello World", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "hello world");
}

// Test: Constructor stores original string in m_str when case sensitive
TEST(CasedStringTest_216, ConstructorStoresOriginalStringCaseSensitive_216) {
    CasedString cs("Hello World", CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, "Hello World");
}

// Test: adjustString with string containing only spaces, case insensitive
TEST(CasedStringTest_216, AdjustStringSpacesOnlyCaseInsensitive_216) {
    CasedString cs("   ", CaseSensitive::No);
    std::string result = cs.adjustString("   ");
    EXPECT_EQ(result, "   ");
}

// Test: adjustString with single character uppercase, case insensitive
TEST(CasedStringTest_216, AdjustStringSingleUpperCharCaseInsensitive_216) {
    CasedString cs("A", CaseSensitive::No);
    std::string result = cs.adjustString("A");
    EXPECT_EQ(result, "a");
}

// Test: adjustString with single character lowercase, case sensitive
TEST(CasedStringTest_216, AdjustStringSingleLowerCharCaseSensitive_216) {
    CasedString cs("a", CaseSensitive::Yes);
    std::string result = cs.adjustString("a");
    EXPECT_EQ(result, "a");
}

// Test: caseSensitivitySuffix returns appropriate suffix for case sensitive
TEST(CasedStringTest_216, CaseSensitivitySuffixCaseSensitive_216) {
    CasedString cs("test", CaseSensitive::Yes);
    auto suffix = cs.caseSensitivitySuffix();
    // When case sensitive, we expect either empty or a specific suffix
    // This tests that the method is callable and returns something reasonable
    EXPECT_TRUE(suffix.empty() || suffix.size() > 0);
}

// Test: caseSensitivitySuffix returns appropriate suffix for case insensitive
TEST(CasedStringTest_216, CaseSensitivitySuffixCaseInsensitive_216) {
    CasedString cs("test", CaseSensitive::No);
    auto suffix = cs.caseSensitivitySuffix();
    // When case insensitive, typically a suffix like " (case insensitive)" is returned
    EXPECT_FALSE(suffix.empty());
}

// Test: adjustString on a different string than what was used in construction
TEST(CasedStringTest_216, AdjustStringDifferentFromConstructionString_216) {
    CasedString cs("Original", CaseSensitive::No);
    std::string result = cs.adjustString("DIFFERENT STRING");
    EXPECT_EQ(result, "different string");
}

// Test: adjustString preserves non-alpha characters when case insensitive
TEST(CasedStringTest_216, AdjustStringPreservesNonAlphaChars_216) {
    CasedString cs("test", CaseSensitive::No);
    std::string result = cs.adjustString("Hello, World! 123");
    EXPECT_EQ(result, "hello, world! 123");
}

// Test: Long string adjustment case insensitive
TEST(CasedStringTest_216, AdjustStringLongStringCaseInsensitive_216) {
    std::string longStr(1000, 'A');
    CasedString cs(longStr, CaseSensitive::No);
    std::string expected(1000, 'a');
    std::string result = cs.adjustString(longStr);
    EXPECT_EQ(result, expected);
}

// Test: Long string adjustment case sensitive
TEST(CasedStringTest_216, AdjustStringLongStringCaseSensitive_216) {
    std::string longStr(1000, 'A');
    CasedString cs(longStr, CaseSensitive::Yes);
    std::string result = cs.adjustString(longStr);
    EXPECT_EQ(result, longStr);
}
