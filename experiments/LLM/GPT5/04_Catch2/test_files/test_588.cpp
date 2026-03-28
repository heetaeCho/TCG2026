// contains_tests_588.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test.
// (In your codebase, prefer including the proper header instead.)
namespace Catch {
    bool contains(std::string const& s, std::string const& infix);
}

using Catch::contains;

namespace {

// Normal operation: infix present somewhere in the middle
TEST(ContainsTest_588, ReturnsTrueWhenInfixPresent_588) {
    EXPECT_TRUE(contains("the quick brown fox", "quick"));
}

// Normal operation: infix not present
TEST(ContainsTest_588, ReturnsFalseWhenInfixAbsent_588) {
    EXPECT_FALSE(contains("the quick brown fox", "slow"));
}

// Boundary: infix at the very start
TEST(ContainsTest_588, ReturnsTrueWhenInfixAtStart_588) {
    EXPECT_TRUE(contains("hello world", "hello"));
}

// Boundary: infix at the very end
TEST(ContainsTest_588, ReturnsTrueWhenInfixAtEnd_588) {
    EXPECT_TRUE(contains("hello world", "world"));
}

// Boundary: infix equals the whole string
TEST(ContainsTest_588, ReturnsTrueWhenInfixEqualsString_588) {
    EXPECT_TRUE(contains("exact", "exact"));
}

// Boundary: empty infix is always found (std::string::find returns 0)
TEST(ContainsTest_588, EmptyInfixAlwaysFound_588) {
    EXPECT_TRUE(contains("anything", ""));
}

// Boundary: empty string with empty infix should be true
TEST(ContainsTest_588, EmptyStringAndEmptyInfix_588) {
    EXPECT_TRUE(contains("", ""));
}

// Boundary: infix longer than the string cannot be found
TEST(ContainsTest_588, InfixLongerThanString_588) {
    EXPECT_FALSE(contains("cat", "catch"));
}

// Behavior: case sensitivity (should be case-sensitive)
TEST(ContainsTest_588, CaseSensitiveComparison_588) {
    EXPECT_FALSE(contains("CaseSensitive", "casesensitive"));
    EXPECT_TRUE(contains("CaseSensitive", "Case"));
}

// Behavior: handles UTF-8 (multi-byte) substrings as byte sequences
TEST(ContainsTest_588, HandlesUtf8Multibyte_588) {
    // "안녕하세요" contains "세요"
    EXPECT_TRUE(contains("안녕하세요", "세요"));
    // "こんにちは" does not contain "こんばんは"
    EXPECT_FALSE(contains("こんにちは", "こんばんは"));
}

} // namespace
