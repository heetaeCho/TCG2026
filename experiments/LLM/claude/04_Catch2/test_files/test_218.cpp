#include <gtest/gtest.h>
#include <string>

// Include necessary Catch2 headers
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch::Matchers;

// Since StringMatcherBase is abstract (inherits from MatcherBase<std::string> which has pure virtual `match`),
// we need a concrete subclass to test `describe()`.
class ConcreteStringMatcher : public StringMatcherBase {
public:
    ConcreteStringMatcher(Catch::StringRef operation, CasedString const& comparator)
        : StringMatcherBase(operation, comparator) {}

    bool match(std::string const& /*source*/) const override {
        return false; // Not relevant for testing describe()
    }
};

class StringMatcherBaseTest_218 : public ::testing::Test {
protected:
};

// Test describe() with case-sensitive matching
TEST_F(StringMatcherBaseTest_218, DescribeCaseSensitive_218) {
    CasedString comparator("hello", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("equals", comparator);

    std::string result = matcher.describe();

    // Expected format: <operation>: "<string>"<caseSensitivitySuffix>
    // For case-sensitive, suffix should be empty or specific value
    EXPECT_NE(result.find("equals"), std::string::npos);
    EXPECT_NE(result.find("\"hello\""), std::string::npos);
}

// Test describe() with case-insensitive matching
TEST_F(StringMatcherBaseTest_218, DescribeCaseInsensitive_218) {
    CasedString comparator("Hello", CaseSensitive::No);
    ConcreteStringMatcher matcher("contains", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("contains"), std::string::npos);
    // When case insensitive, the string should be adjusted (likely lowercased)
    // and there should be a case insensitivity suffix
    EXPECT_NE(result.find("\""), std::string::npos);
    // The suffix for case insensitive should be present (e.g., " (case insensitive)")
    EXPECT_NE(result.find("case insensitive"), std::string::npos);
}

// Test describe() with empty string comparator
TEST_F(StringMatcherBaseTest_218, DescribeEmptyString_218) {
    CasedString comparator("", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("starts with", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("starts with"), std::string::npos);
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

// Test describe() with empty operation
TEST_F(StringMatcherBaseTest_218, DescribeEmptyOperation_218) {
    CasedString comparator("test", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find(": \"test\""), std::string::npos);
}

// Test describe() with special characters in the string
TEST_F(StringMatcherBaseTest_218, DescribeSpecialCharacters_218) {
    CasedString comparator("he\"llo", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("equals", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("equals"), std::string::npos);
    EXPECT_NE(result.find("he\"llo"), std::string::npos);
}

// Test describe() format structure: operation + ": \"" + string + "\"" + suffix
TEST_F(StringMatcherBaseTest_218, DescribeFormatStructureCaseSensitive_218) {
    CasedString comparator("world", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("matches", comparator);

    std::string result = matcher.describe();

    // For case sensitive, the suffix should be empty, so expect:
    // "matches: \"world\""
    // The result should start with the operation
    EXPECT_EQ(result.substr(0, 7), "matches");
    EXPECT_NE(result.find(": \"world\""), std::string::npos);
}

// Test describe() with long string
TEST_F(StringMatcherBaseTest_218, DescribeLongString_218) {
    std::string longStr(1000, 'a');
    CasedString comparator(longStr, CaseSensitive::Yes);
    ConcreteStringMatcher matcher("contains", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("contains"), std::string::npos);
    EXPECT_NE(result.find(longStr), std::string::npos);
}

// Test describe() with case insensitive and verify string is adjusted
TEST_F(StringMatcherBaseTest_218, DescribeCaseInsensitiveStringAdjusted_218) {
    CasedString comparator("HELLO", CaseSensitive::No);
    ConcreteStringMatcher matcher("equals", comparator);

    std::string result = matcher.describe();

    // When case insensitive, the string should be lowercased
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test CasedString adjustString for case sensitive (should preserve original)
TEST_F(StringMatcherBaseTest_218, CasedStringCaseSensitivePreservesCase_218) {
    CasedString cs("HeLLo", CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, "HeLLo");
}

// Test CasedString adjustString for case insensitive (should lowercase)
TEST_F(StringMatcherBaseTest_218, CasedStringCaseInsensitiveLowercases_218) {
    CasedString cs("HeLLo", CaseSensitive::No);
    EXPECT_EQ(cs.m_str, "hello");
}

// Test CasedString caseSensitivitySuffix for case sensitive
TEST_F(StringMatcherBaseTest_218, CaseSensitivitySuffixCaseSensitive_218) {
    CasedString cs("test", CaseSensitive::Yes);
    Catch::StringRef suffix = cs.caseSensitivitySuffix();
    // Case sensitive should have empty suffix
    EXPECT_TRUE(suffix.empty());
}

// Test CasedString caseSensitivitySuffix for case insensitive
TEST_F(StringMatcherBaseTest_218, CaseSensitivitySuffixCaseInsensitive_218) {
    CasedString cs("test", CaseSensitive::No);
    Catch::StringRef suffix = cs.caseSensitivitySuffix();
    // Case insensitive should have a non-empty suffix
    EXPECT_FALSE(suffix.empty());
}

// Test CasedString with empty string
TEST_F(StringMatcherBaseTest_218, CasedStringEmptyString_218) {
    CasedString cs("", CaseSensitive::Yes);
    EXPECT_EQ(cs.m_str, "");

    CasedString csInsensitive("", CaseSensitive::No);
    EXPECT_EQ(csInsensitive.m_str, "");
}

// Test describe() with whitespace-only string
TEST_F(StringMatcherBaseTest_218, DescribeWhitespaceString_218) {
    CasedString comparator("   ", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("equals", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("\"   \""), std::string::npos);
}

// Test describe() with different operations
TEST_F(StringMatcherBaseTest_218, DescribeEndsWithOperation_218) {
    CasedString comparator("suffix", CaseSensitive::Yes);
    ConcreteStringMatcher matcher("ends with", comparator);

    std::string result = matcher.describe();

    EXPECT_NE(result.find("ends with"), std::string::npos);
    EXPECT_NE(result.find("\"suffix\""), std::string::npos);
}
