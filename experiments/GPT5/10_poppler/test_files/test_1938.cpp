#include <gtest/gtest.h>
#include <string_view>

// Include the header file with the partial code
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

// Test case class for the removeTrailingSpaces function
class RemoveTrailingSpacesTest_1938 : public ::testing::Test {
protected:
    // Any necessary setup or teardown can be done here
};

// Normal Operation Test
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_NormalOperation) {
    std::string_view input = "Hello World   ";
    std::string_view expected = "Hello World";

    // Verify the function correctly removes the trailing spaces
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}

// Boundary Condition Test - Empty string
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_EmptyString) {
    std::string_view input = "";
    std::string_view expected = "";

    // Verify that an empty string remains unchanged
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}

// Boundary Condition Test - String with only spaces
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_OnlySpaces) {
    std::string_view input = "     ";
    std::string_view expected = "";

    // Verify that a string with only spaces becomes empty
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}

// Boundary Condition Test - No trailing spaces
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_NoTrailingSpaces) {
    std::string_view input = "NoTrailingSpaces";
    std::string_view expected = "NoTrailingSpaces";

    // Verify that a string with no trailing spaces is unaffected
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}

// Exceptional Case Test - String with all characters as non-space
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_OnlyNonSpaceChars) {
    std::string_view input = "NoSpacesHere";
    std::string_view expected = "NoSpacesHere";

    // Verify that a string without trailing spaces remains unchanged
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}

// Exceptional Case Test - String with no non-space characters
TEST_F(RemoveTrailingSpacesTest_1938, RemoveTrailingSpaces_AllSpaces) {
    std::string_view input = "     ";
    std::string_view expected = "";

    // Verify that a string composed only of spaces is stripped
    EXPECT_EQ(DN::detail::removeTrailingSpaces(input), expected);
}