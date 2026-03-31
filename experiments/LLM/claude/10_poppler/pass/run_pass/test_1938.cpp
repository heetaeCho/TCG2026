#include <gtest/gtest.h>
#include <string_view>
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

class RemoveTrailingSpacesTest_1938 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(RemoveTrailingSpacesTest_1938, NoTrailingSpaces_1938)
{
    std::string_view input = "hello";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveTrailingSpacesTest_1938, SingleTrailingSpace_1938)
{
    std::string_view input = "hello ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveTrailingSpacesTest_1938, MultipleTrailingSpaces_1938)
{
    std::string_view input = "hello   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(RemoveTrailingSpacesTest_1938, LeadingSpacesPreserved_1938)
{
    std::string_view input = "   hello";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "   hello");
}

TEST_F(RemoveTrailingSpacesTest_1938, LeadingAndTrailingSpaces_1938)
{
    std::string_view input = "   hello   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "   hello");
}

TEST_F(RemoveTrailingSpacesTest_1938, SpacesInMiddle_1938)
{
    std::string_view input = "hello world";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello world");
}

TEST_F(RemoveTrailingSpacesTest_1938, SpacesInMiddleAndTrailing_1938)
{
    std::string_view input = "hello world   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello world");
}

// Boundary condition tests

TEST_F(RemoveTrailingSpacesTest_1938, EmptyString_1938)
{
    std::string_view input = "";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(RemoveTrailingSpacesTest_1938, AllSpaces_1938)
{
    std::string_view input = "     ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(RemoveTrailingSpacesTest_1938, SingleSpace_1938)
{
    std::string_view input = " ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(RemoveTrailingSpacesTest_1938, SingleCharacter_1938)
{
    std::string_view input = "a";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "a");
}

TEST_F(RemoveTrailingSpacesTest_1938, SingleCharacterWithTrailingSpace_1938)
{
    std::string_view input = "a ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "a");
}

TEST_F(RemoveTrailingSpacesTest_1938, SingleCharacterWithMultipleTrailingSpaces_1938)
{
    std::string_view input = "a    ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "a");
}

// Tests with special characters

TEST_F(RemoveTrailingSpacesTest_1938, TabsNotRemoved_1938)
{
    std::string_view input = "hello\t";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello\t");
}

TEST_F(RemoveTrailingSpacesTest_1938, NewlineNotRemoved_1938)
{
    std::string_view input = "hello\n";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello\n");
}

TEST_F(RemoveTrailingSpacesTest_1938, MixedWhitespaceOnlySpacesRemoved_1938)
{
    std::string_view input = "hello\t   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello\t");
}

TEST_F(RemoveTrailingSpacesTest_1938, TabFollowedBySpaces_1938)
{
    std::string_view input = "hello \t ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "hello \t");
}

// DN-style content tests

TEST_F(RemoveTrailingSpacesTest_1938, DistinguishedNameContent_1938)
{
    std::string_view input = "CN=John Doe   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "CN=John Doe");
}

TEST_F(RemoveTrailingSpacesTest_1938, DistinguishedNameNoTrailing_1938)
{
    std::string_view input = "OU=Engineering";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result, "OU=Engineering");
}

TEST_F(RemoveTrailingSpacesTest_1938, ResultSizeIsCorrect_1938)
{
    std::string_view input = "test   ";
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result.size(), 4u);
}

TEST_F(RemoveTrailingSpacesTest_1938, LongStringOfSpaces_1938)
{
    std::string input_str(1000, ' ');
    std::string_view input(input_str);
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_TRUE(result.empty());
}

TEST_F(RemoveTrailingSpacesTest_1938, LongStringWithTrailingSpaces_1938)
{
    std::string input_str(500, 'x');
    input_str += std::string(500, ' ');
    std::string_view input(input_str);
    auto result = DN::detail::removeTrailingSpaces(input);
    EXPECT_EQ(result.size(), 500u);
    EXPECT_EQ(result, std::string_view(input_str.data(), 500));
}
