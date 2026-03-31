#include <gtest/gtest.h>
#include <string_view>
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

class RemoveLeadingSpacesTest_1937 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(RemoveLeadingSpacesTest_1937, NoLeadingSpaces_1937)
{
    std::string_view input = "hello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveLeadingSpacesTest_1937, SingleLeadingSpace_1937)
{
    std::string_view input = " hello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveLeadingSpacesTest_1937, MultipleLeadingSpaces_1937)
{
    std::string_view input = "    hello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveLeadingSpacesTest_1937, LeadingSpacesWithTrailingSpaces_1937)
{
    std::string_view input = "   hello   ";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello   ");
}

TEST_F(RemoveLeadingSpacesTest_1937, SpacesInMiddle_1937)
{
    std::string_view input = "hello world";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello world");
}

TEST_F(RemoveLeadingSpacesTest_1937, LeadingSpacesWithSpacesInMiddle_1937)
{
    std::string_view input = "  hello world";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "hello world");
}

// Boundary condition tests

TEST_F(RemoveLeadingSpacesTest_1937, EmptyString_1937)
{
    std::string_view input = "";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, "");
}

TEST_F(RemoveLeadingSpacesTest_1937, AllSpaces_1937)
{
    std::string_view input = "     ";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_TRUE(result.empty());
}

TEST_F(RemoveLeadingSpacesTest_1937, SingleSpace_1937)
{
    std::string_view input = " ";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_TRUE(result.empty());
}

TEST_F(RemoveLeadingSpacesTest_1937, SingleNonSpaceCharacter_1937)
{
    std::string_view input = "x";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "x");
}

TEST_F(RemoveLeadingSpacesTest_1937, SingleSpaceFollowedBySingleChar_1937)
{
    std::string_view input = " x";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "x");
}

// Tests with non-space whitespace characters (tabs, newlines should NOT be removed since only ' ' is targeted)

TEST_F(RemoveLeadingSpacesTest_1937, LeadingTabNotRemoved_1937)
{
    std::string_view input = "\thello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "\thello");
}

TEST_F(RemoveLeadingSpacesTest_1937, LeadingNewlineNotRemoved_1937)
{
    std::string_view input = "\nhello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "\nhello");
}

TEST_F(RemoveLeadingSpacesTest_1937, MixedWhitespaceOnlySpacesRemoved_1937)
{
    std::string_view input = "  \thello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "\thello");
}

TEST_F(RemoveLeadingSpacesTest_1937, TabThenSpaceThenText_1937)
{
    std::string_view input = "\t hello";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "\t hello");
}

// Test that the returned view refers to the correct substring

TEST_F(RemoveLeadingSpacesTest_1937, ReturnedViewIsSubview_1937)
{
    std::string_view input = "   test";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result, "test");
    // Verify it points into the original data
    EXPECT_EQ(result.data(), input.data() + 3);
}

TEST_F(RemoveLeadingSpacesTest_1937, NoSpacesReturnsSameView_1937)
{
    std::string_view input = "test";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result.data(), input.data());
    EXPECT_EQ(result.size(), input.size());
}

// Large number of leading spaces

TEST_F(RemoveLeadingSpacesTest_1937, ManyLeadingSpaces_1937)
{
    std::string spaces(1000, ' ');
    std::string str = spaces + "data";
    std::string_view input(str);
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "data");
}

TEST_F(RemoveLeadingSpacesTest_1937, ManySpacesOnly_1937)
{
    std::string spaces(1000, ' ');
    std::string_view input(spaces);
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_TRUE(result.empty());
}

// Special characters

TEST_F(RemoveLeadingSpacesTest_1937, SpecialCharactersPreserved_1937)
{
    std::string_view input = "  CN=John Doe,O=Example";
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result, "CN=John Doe,O=Example");
}

TEST_F(RemoveLeadingSpacesTest_1937, NullCharacterInString_1937)
{
    const char data[] = "  \0hello";
    std::string_view input(data, sizeof(data) - 1);
    auto result = DN::detail::removeLeadingSpaces(input);
    EXPECT_EQ(result.size(), sizeof(data) - 1 - 2); // removed 2 leading spaces
    EXPECT_EQ(result[0], '\0');
}
