// trim_tests_592.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declaration based on provided interface.
namespace Catch {
    std::string trim(std::string const& str);
}

namespace {

// No surrounding whitespace => unchanged
TEST(TrimTest_592, NoWhitespaceReturnsSame_592) {
    std::string input = "abcDEF123";
    EXPECT_EQ(Catch::trim(input), "abcDEF123");
}

// Only leading spaces are removed
TEST(TrimTest_592, LeadingSpacesTrimmed_592) {
    std::string input = "   leading";
    EXPECT_EQ(Catch::trim(input), "leading");
}

// Only trailing tabs are removed
TEST(TrimTest_592, TrailingTabsTrimmed_592) {
    std::string input = "trailing\t\t\t";
    EXPECT_EQ(Catch::trim(input), "trailing");
}

// Mixed leading/trailing whitespace (spaces, tabs, newlines, carriage returns) are removed
TEST(TrimTest_592, MixedLeadingTrailingWhitespaceTrimmed_592) {
    std::string input = "\n \tvalue\r\t ";
    EXPECT_EQ(Catch::trim(input), "value");
}

// Internal whitespace/newlines are preserved
TEST(TrimTest_592, InternalWhitespacePreserved_592) {
    std::string input = " a b\tc \n d ";
    // Only the outermost whitespace should be removed; internal whitespace remains
    EXPECT_EQ(Catch::trim(input), "a b\tc \n d");
}

// Entirely whitespace => empty string
TEST(TrimTest_592, OnlyWhitespaceReturnsEmpty_592) {
    std::string input = " \t\r\n \t";
    EXPECT_EQ(Catch::trim(input), "");
}

// Empty string => empty string
TEST(TrimTest_592, EmptyStringReturnsEmpty_592) {
    std::string input = "";
    EXPECT_EQ(Catch::trim(input), "");
}

// Single non-whitespace char surrounded by whitespace
TEST(TrimTest_592, SingleCharBetweenWhitespace_592) {
    std::string input = "\t a \n";
    EXPECT_EQ(Catch::trim(input), "a");
}

// Last non-whitespace at index 0 after trimming tail
TEST(TrimTest_592, TrailingWhitespaceOnly_592) {
    std::string input = "a   \t";
    EXPECT_EQ(Catch::trim(input), "a");
}

// First non-whitespace at last index after trimming head
TEST(TrimTest_592, LeadingWhitespaceOnly_592) {
    std::string input = " \n\t\rz";
    EXPECT_EQ(Catch::trim(input), "z");
}

} // namespace
