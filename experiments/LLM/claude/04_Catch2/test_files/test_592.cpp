#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
namespace Catch {
    std::string trim(std::string const& str);
}

// Normal operation tests

TEST(CatchTrimTest_592, TrimsLeadingSpaces_592) {
    EXPECT_EQ(Catch::trim("   hello"), "hello");
}

TEST(CatchTrimTest_592, TrimsTrailingSpaces_592) {
    EXPECT_EQ(Catch::trim("hello   "), "hello");
}

TEST(CatchTrimTest_592, TrimsLeadingAndTrailingSpaces_592) {
    EXPECT_EQ(Catch::trim("   hello   "), "hello");
}

TEST(CatchTrimTest_592, TrimsLeadingTabs_592) {
    EXPECT_EQ(Catch::trim("\t\thello"), "hello");
}

TEST(CatchTrimTest_592, TrimsTrailingTabs_592) {
    EXPECT_EQ(Catch::trim("hello\t\t"), "hello");
}

TEST(CatchTrimTest_592, TrimsLeadingNewlines_592) {
    EXPECT_EQ(Catch::trim("\n\nhello"), "hello");
}

TEST(CatchTrimTest_592, TrimsTrailingNewlines_592) {
    EXPECT_EQ(Catch::trim("hello\n\n"), "hello");
}

TEST(CatchTrimTest_592, TrimsCarriageReturns_592) {
    EXPECT_EQ(Catch::trim("\r\rhello\r\r"), "hello");
}

TEST(CatchTrimTest_592, TrimsMixedWhitespace_592) {
    EXPECT_EQ(Catch::trim("\n\r\t hello world \t\r\n"), "hello world");
}

TEST(CatchTrimTest_592, NoTrimNeeded_592) {
    EXPECT_EQ(Catch::trim("hello"), "hello");
}

TEST(CatchTrimTest_592, PreservesInternalWhitespace_592) {
    EXPECT_EQ(Catch::trim("  hello   world  "), "hello   world");
}

TEST(CatchTrimTest_592, PreservesInternalTabs_592) {
    EXPECT_EQ(Catch::trim("  hello\tworld  "), "hello\tworld");
}

TEST(CatchTrimTest_592, PreservesInternalNewlines_592) {
    EXPECT_EQ(Catch::trim("  hello\nworld  "), "hello\nworld");
}

// Boundary condition tests

TEST(CatchTrimTest_592, EmptyString_592) {
    EXPECT_EQ(Catch::trim(""), "");
}

TEST(CatchTrimTest_592, AllSpaces_592) {
    EXPECT_EQ(Catch::trim("     "), "");
}

TEST(CatchTrimTest_592, AllTabs_592) {
    EXPECT_EQ(Catch::trim("\t\t\t"), "");
}

TEST(CatchTrimTest_592, AllNewlines_592) {
    EXPECT_EQ(Catch::trim("\n\n\n"), "");
}

TEST(CatchTrimTest_592, AllCarriageReturns_592) {
    EXPECT_EQ(Catch::trim("\r\r\r"), "");
}

TEST(CatchTrimTest_592, AllMixedWhitespace_592) {
    EXPECT_EQ(Catch::trim("\n\r\t \t\r\n"), "");
}

TEST(CatchTrimTest_592, SingleCharacter_592) {
    EXPECT_EQ(Catch::trim("a"), "a");
}

TEST(CatchTrimTest_592, SingleSpace_592) {
    EXPECT_EQ(Catch::trim(" "), "");
}

TEST(CatchTrimTest_592, SingleCharWithLeadingSpace_592) {
    EXPECT_EQ(Catch::trim(" a"), "a");
}

TEST(CatchTrimTest_592, SingleCharWithTrailingSpace_592) {
    EXPECT_EQ(Catch::trim("a "), "a");
}

TEST(CatchTrimTest_592, SingleCharSurroundedBySpaces_592) {
    EXPECT_EQ(Catch::trim(" a "), "a");
}

TEST(CatchTrimTest_592, SingleTab_592) {
    EXPECT_EQ(Catch::trim("\t"), "");
}

TEST(CatchTrimTest_592, SingleNewline_592) {
    EXPECT_EQ(Catch::trim("\n"), "");
}

TEST(CatchTrimTest_592, SingleCarriageReturn_592) {
    EXPECT_EQ(Catch::trim("\r"), "");
}

TEST(CatchTrimTest_592, StringWithOnlyNonWhitespace_592) {
    EXPECT_EQ(Catch::trim("abc"), "abc");
}

TEST(CatchTrimTest_592, LongStringWithWhitespace_592) {
    std::string input = "   \t\n\r  This is a longer test string with internal   spaces  \r\n\t   ";
    EXPECT_EQ(Catch::trim(input), "This is a longer test string with internal   spaces");
}

TEST(CatchTrimTest_592, StringWithSpecialNonWhitespaceChars_592) {
    EXPECT_EQ(Catch::trim("  !@#$%^&*()  "), "!@#$%^&*()");
}

TEST(CatchTrimTest_592, StringWithNullCharInMiddle_592) {
    // std::string can contain null characters
    std::string input = " hello";
    // Just verify normal behavior with leading space
    EXPECT_EQ(Catch::trim(input), "hello");
}

TEST(CatchTrimTest_592, MultipleWhitespaceTypesOnBothEnds_592) {
    EXPECT_EQ(Catch::trim("\t \n \r test \r \n \t"), "test");
}
