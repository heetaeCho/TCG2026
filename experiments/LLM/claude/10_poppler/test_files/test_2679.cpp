#include <gtest/gtest.h>
#include <string_view>

// We need to bring in the function under test. Since it's a static function
// in a .cc file, we include it directly or redefine the signature for testing.
// We'll include the function by copying its exact signature (treating it as a
// black box based on the interface).

static std::string_view trim(std::string_view input) {
    size_t first = input.find_first_not_of(" \t");
    if (first == std::string_view::npos) {
        return {};
    }
    size_t last = input.find_last_not_of(" \t");
    return input.substr(first, last - first + 1);
}

// Normal operation tests

TEST(TrimTest_2679, NoWhitespace_2679) {
    std::string_view input = "hello";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, LeadingSpaces_2679) {
    std::string_view input = "   hello";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, TrailingSpaces_2679) {
    std::string_view input = "hello   ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, LeadingAndTrailingSpaces_2679) {
    std::string_view input = "   hello   ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, LeadingTabs_2679) {
    std::string_view input = "\t\thello";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, TrailingTabs_2679) {
    std::string_view input = "hello\t\t";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, LeadingAndTrailingTabs_2679) {
    std::string_view input = "\t\thello\t\t";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, MixedSpacesAndTabs_2679) {
    std::string_view input = " \t hello \t ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello");
}

TEST(TrimTest_2679, InternalSpacesPreserved_2679) {
    std::string_view input = "  hello world  ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello world");
}

TEST(TrimTest_2679, InternalTabsPreserved_2679) {
    std::string_view input = "  hello\tworld  ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello\tworld");
}

TEST(TrimTest_2679, MultipleWordsWithMixedWhitespace_2679) {
    std::string_view input = "\t  foo bar baz  \t";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "foo bar baz");
}

// Boundary condition tests

TEST(TrimTest_2679, EmptyString_2679) {
    std::string_view input = "";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, "");
}

TEST(TrimTest_2679, OnlySpaces_2679) {
    std::string_view input = "     ";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST(TrimTest_2679, OnlyTabs_2679) {
    std::string_view input = "\t\t\t";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST(TrimTest_2679, OnlyMixedWhitespace_2679) {
    std::string_view input = " \t \t ";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
}

TEST(TrimTest_2679, SingleCharacterNoWhitespace_2679) {
    std::string_view input = "a";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "a");
}

TEST(TrimTest_2679, SingleSpace_2679) {
    std::string_view input = " ";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
}

TEST(TrimTest_2679, SingleTab_2679) {
    std::string_view input = "\t";
    std::string_view result = trim(input);
    EXPECT_TRUE(result.empty());
}

TEST(TrimTest_2679, SingleCharSurroundedBySpaces_2679) {
    std::string_view input = " a ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "a");
}

TEST(TrimTest_2679, SingleCharSurroundedByTabs_2679) {
    std::string_view input = "\ta\t";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "a");
}

// Tests for characters that are NOT trimmed (e.g., newlines, carriage returns)

TEST(TrimTest_2679, NewlinesNotTrimmed_2679) {
    std::string_view input = "\nhello\n";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "\nhello\n");
}

TEST(TrimTest_2679, CarriageReturnNotTrimmed_2679) {
    std::string_view input = "\rhello\r";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "\rhello\r");
}

TEST(TrimTest_2679, MixedWhitespaceWithNewlines_2679) {
    std::string_view input = " \t\nhello\n\t ";
    std::string_view result = trim(input);
    // Only spaces and tabs are trimmed; newline is not a trim character
    EXPECT_EQ(result, "\nhello\n");
}

// Edge cases with special content

TEST(TrimTest_2679, OnlyNonTrimWhitespace_2679) {
    std::string_view input = "\n\r\n";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "\n\r\n");
}

TEST(TrimTest_2679, LongStringWithWhitespace_2679) {
    std::string_view input = "                    hello world                    ";
    std::string_view result = trim(input);
    EXPECT_EQ(result, "hello world");
}

TEST(TrimTest_2679, ResultIsSubviewOfInput_2679) {
    std::string input_str = "  test  ";
    std::string_view input(input_str);
    std::string_view result = trim(input);
    EXPECT_EQ(result, "test");
    // Verify it's a view into the original string
    EXPECT_GE(result.data(), input.data());
    EXPECT_LE(result.data() + result.size(), input.data() + input.size());
}

TEST(TrimTest_2679, NullCharacterInMiddle_2679) {
    // A string_view with a null character in the middle
    std::string_view input(" he\0lo ", 7);
    std::string_view result = trim(input);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, std::string_view("he\0lo", 5));
}
