#include <gtest/gtest.h>
#include <string>

// Include the necessary headers
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/catch_case_sensitive.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;
using namespace Catch::Matchers;

class CasedStringTest_217 : public ::testing::Test {
protected:
    // Helper to convert StringRef to std::string for comparison
    std::string toStdString(StringRef sr) {
        return std::string(sr.data(), sr.size());
    }
};

// Test that caseSensitivitySuffix returns empty string when CaseSensitive::Yes
TEST_F(CasedStringTest_217, CaseSensitivitySuffixReturnsEmptyWhenCaseSensitiveYes_217) {
    CasedString cs("hello", CaseSensitive::Yes);
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), "");
}

// Test that caseSensitivitySuffix returns " (case insensitive)" when CaseSensitive::No
TEST_F(CasedStringTest_217, CaseSensitivitySuffixReturnsSuffixWhenCaseSensitiveNo_217) {
    CasedString cs("hello", CaseSensitive::No);
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), " (case insensitive)");
}

// Test with empty string and CaseSensitive::Yes
TEST_F(CasedStringTest_217, EmptyStringCaseSensitiveYes_217) {
    CasedString cs("", CaseSensitive::Yes);
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), "");
}

// Test with empty string and CaseSensitive::No
TEST_F(CasedStringTest_217, EmptyStringCaseSensitiveNo_217) {
    CasedString cs("", CaseSensitive::No);
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), " (case insensitive)");
}

// Test that m_str is accessible and stores the string (public member)
TEST_F(CasedStringTest_217, MStrStoresStringCaseSensitiveYes_217) {
    CasedString cs("TestString", CaseSensitive::Yes);
    // m_str is public, so we can access it
    // With CaseSensitive::Yes, adjustString should keep the string as-is
    EXPECT_EQ(cs.m_str, "TestString");
}

// Test that m_str with CaseSensitive::No might adjust (e.g., lowercase) the string
TEST_F(CasedStringTest_217, MStrStoresAdjustedStringCaseSensitiveNo_217) {
    CasedString cs("TestString", CaseSensitive::No);
    // With CaseSensitive::No, adjustString likely lowercases the string
    EXPECT_EQ(cs.m_str, "teststring");
}

// Test adjustString with CaseSensitive::Yes preserves case
TEST_F(CasedStringTest_217, AdjustStringPreservesCaseWhenCaseSensitiveYes_217) {
    CasedString cs("MiXeD CaSe", CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, "MiXeD CaSe");
}

// Test adjustString with CaseSensitive::No lowercases
TEST_F(CasedStringTest_217, AdjustStringLowersCaseWhenCaseSensitiveNo_217) {
    CasedString cs("MiXeD CaSe", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "mixed case");
}

// Test with special characters
TEST_F(CasedStringTest_217, SpecialCharactersCaseSensitiveYes_217) {
    CasedString cs("Hello!@#$%", CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, "Hello!@#$%");
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), "");
}

// Test with special characters case insensitive
TEST_F(CasedStringTest_217, SpecialCharactersCaseSensitiveNo_217) {
    CasedString cs("Hello!@#$%", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "hello!@#$%");
    StringRef result = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result), " (case insensitive)");
}

// Test with numeric string
TEST_F(CasedStringTest_217, NumericStringCaseSensitiveNo_217) {
    CasedString cs("12345", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "12345");
}

// Test with all uppercase
TEST_F(CasedStringTest_217, AllUppercaseCaseSensitiveNo_217) {
    CasedString cs("ABCDEF", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "abcdef");
}

// Test with all lowercase
TEST_F(CasedStringTest_217, AllLowercaseCaseSensitiveNo_217) {
    CasedString cs("abcdef", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "abcdef");
}

// Test with whitespace string
TEST_F(CasedStringTest_217, WhitespaceStringCaseSensitiveNo_217) {
    CasedString cs("   ", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "   ");
}

// Test suffix is consistent across multiple calls
TEST_F(CasedStringTest_217, CaseSensitivitySuffixConsistentAcrossMultipleCalls_217) {
    CasedString cs("test", CaseSensitive::No);
    StringRef result1 = cs.caseSensitivitySuffix();
    StringRef result2 = cs.caseSensitivitySuffix();
    EXPECT_EQ(toStdString(result1), toStdString(result2));
}
