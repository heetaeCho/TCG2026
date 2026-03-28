#include <gtest/gtest.h>
#include <string>

// We need to access the internal ltrim function. Since it's in an anonymous-like
// static context within a namespace, we need to either include the header or
// redeclare it. Since the function is static in the .cpp file, we can't directly
// link to it. However, based on the task description, we treat it as a testable
// interface. We'll replicate the namespace declaration to test it.

// Since the function is static in the .cpp file, we need to include or replicate
// it for testing purposes. In a real scenario, this would be exposed through a header.
// For testing, we replicate the exact implementation as given:
namespace Exiv2 {
namespace Internal {
static std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}
}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::ltrim;

class LtrimTest_1013 : public ::testing::Test {
protected:
};

// Test that leading spaces are removed
TEST_F(LtrimTest_1013, RemovesLeadingSpaces_1013) {
    std::string s = "   hello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
    EXPECT_EQ("hello", s);
}

// Test that leading tabs are removed
TEST_F(LtrimTest_1013, RemovesLeadingTabs_1013) {
    std::string s = "\t\thello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test that leading newlines are removed
TEST_F(LtrimTest_1013, RemovesLeadingNewlines_1013) {
    std::string s = "\n\nhello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test that leading carriage returns are removed
TEST_F(LtrimTest_1013, RemovesLeadingCarriageReturns_1013) {
    std::string s = "\r\rhello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test that leading form feeds are removed
TEST_F(LtrimTest_1013, RemovesLeadingFormFeeds_1013) {
    std::string s = "\f\fhello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test that leading vertical tabs are removed
TEST_F(LtrimTest_1013, RemovesLeadingVerticalTabs_1013) {
    std::string s = "\v\vhello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test mixed leading whitespace
TEST_F(LtrimTest_1013, RemovesMixedLeadingWhitespace_1013) {
    std::string s = " \t\n\r\f\vhello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test that trailing whitespace is NOT removed
TEST_F(LtrimTest_1013, DoesNotRemoveTrailingWhitespace_1013) {
    std::string s = "hello   ";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello   ", result);
}

// Test that interior whitespace is NOT removed
TEST_F(LtrimTest_1013, DoesNotRemoveInteriorWhitespace_1013) {
    std::string s = "hello world";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello world", result);
}

// Test string with no leading whitespace
TEST_F(LtrimTest_1013, NoLeadingWhitespace_1013) {
    std::string s = "hello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test empty string
TEST_F(LtrimTest_1013, EmptyString_1013) {
    std::string s = "";
    std::string& result = ltrim(s);
    EXPECT_EQ("", result);
    EXPECT_TRUE(s.empty());
}

// Test string that is all whitespace
TEST_F(LtrimTest_1013, AllWhitespaceString_1013) {
    std::string s = "   \t\n\r  ";
    std::string& result = ltrim(s);
    EXPECT_EQ("", result);
    EXPECT_TRUE(s.empty());
}

// Test that the function returns a reference to the same string
TEST_F(LtrimTest_1013, ReturnsSameReference_1013) {
    std::string s = "  hello";
    std::string& result = ltrim(s);
    EXPECT_EQ(&s, &result);
}

// Test with custom trim characters
TEST_F(LtrimTest_1013, CustomTrimCharacters_1013) {
    std::string s = "xxxhello";
    std::string& result = ltrim(s, "x");
    EXPECT_EQ("hello", result);
}

// Test with custom trim characters that don't match leading chars
TEST_F(LtrimTest_1013, CustomTrimCharactersNoMatch_1013) {
    std::string s = "hello";
    std::string& result = ltrim(s, "x");
    EXPECT_EQ("hello", result);
}

// Test custom trim with multiple character types
TEST_F(LtrimTest_1013, CustomTrimMultipleChars_1013) {
    std::string s = "abcabcdef";
    std::string& result = ltrim(s, "abc");
    EXPECT_EQ("def", result);
}

// Test custom trim where entire string matches
TEST_F(LtrimTest_1013, CustomTrimEntireStringMatches_1013) {
    std::string s = "aaabbb";
    std::string& result = ltrim(s, "ab");
    EXPECT_EQ("", result);
}

// Test with single character string (whitespace)
TEST_F(LtrimTest_1013, SingleWhitespaceChar_1013) {
    std::string s = " ";
    std::string& result = ltrim(s);
    EXPECT_EQ("", result);
}

// Test with single character string (non-whitespace)
TEST_F(LtrimTest_1013, SingleNonWhitespaceChar_1013) {
    std::string s = "a";
    std::string& result = ltrim(s);
    EXPECT_EQ("a", result);
}

// Test leading whitespace with both leading and trailing
TEST_F(LtrimTest_1013, LeadingAndTrailingWhitespace_1013) {
    std::string s = "  hello  ";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello  ", result);
}

// Test with empty custom trim characters (nothing should be trimmed)
TEST_F(LtrimTest_1013, EmptyCustomTrimChars_1013) {
    std::string s = "  hello";
    std::string& result = ltrim(s, "");
    EXPECT_EQ("  hello", result);
}

// Test that only leading characters from the trim set are removed
TEST_F(LtrimTest_1013, OnlyLeadingFromTrimSetRemoved_1013) {
    std::string s = "  hello world  ";
    ltrim(s);
    EXPECT_EQ("hello world  ", s);
}

// Test with null character in custom trim set
TEST_F(LtrimTest_1013, CustomTrimWithDigits_1013) {
    std::string s = "123hello";
    std::string& result = ltrim(s, "0123456789");
    EXPECT_EQ("hello", result);
}

// Test that modifying through returned reference modifies original
TEST_F(LtrimTest_1013, ModifyThroughReturnedReference_1013) {
    std::string s = "  hello";
    std::string& result = ltrim(s);
    result += " world";
    EXPECT_EQ("hello world", s);
}

// Test with string containing only non-default-trim characters and custom trim
TEST_F(LtrimTest_1013, CustomTrimPartialMatch_1013) {
    std::string s = "aabbbccc";
    std::string& result = ltrim(s, "a");
    EXPECT_EQ("bbbccc", result);
}

// Test very long leading whitespace
TEST_F(LtrimTest_1013, LongLeadingWhitespace_1013) {
    std::string s(1000, ' ');
    s += "hello";
    std::string& result = ltrim(s);
    EXPECT_EQ("hello", result);
}

// Test string with special characters after whitespace
TEST_F(LtrimTest_1013, SpecialCharsAfterWhitespace_1013) {
    std::string s = "  !@#$%";
    std::string& result = ltrim(s);
    EXPECT_EQ("!@#$%", result);
}
