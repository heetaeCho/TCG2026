#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Include the header under test
#include "tags_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for StringTagDetails
class StringTagDetailsTest_177 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: equality with matching string_view
TEST_F(StringTagDetailsTest_177, EqualityWithMatchingStringView_177) {
    StringTagDetails details;
    details.val_ = "TestTag";
    EXPECT_TRUE(details == std::string_view("TestTag"));
}

// Normal operation: inequality with non-matching string_view
TEST_F(StringTagDetailsTest_177, InequalityWithNonMatchingStringView_177) {
    StringTagDetails details;
    details.val_ = "TestTag";
    EXPECT_FALSE(details == std::string_view("OtherTag"));
}

// Boundary condition: empty string matches empty val_
TEST_F(StringTagDetailsTest_177, EmptyStringMatchesEmptyVal_177) {
    StringTagDetails details;
    details.val_ = "";
    EXPECT_TRUE(details == std::string_view(""));
}

// Boundary condition: empty string does not match non-empty val_
TEST_F(StringTagDetailsTest_177, EmptyStringDoesNotMatchNonEmptyVal_177) {
    StringTagDetails details;
    details.val_ = "NonEmpty";
    EXPECT_FALSE(details == std::string_view(""));
}

// Boundary condition: non-empty string does not match empty val_
TEST_F(StringTagDetailsTest_177, NonEmptyStringDoesNotMatchEmptyVal_177) {
    StringTagDetails details;
    details.val_ = "";
    EXPECT_FALSE(details == std::string_view("NonEmpty"));
}

// Boundary condition: case sensitivity - different case should not match
TEST_F(StringTagDetailsTest_177, CaseSensitivity_177) {
    StringTagDetails details;
    details.val_ = "TestTag";
    EXPECT_FALSE(details == std::string_view("testtag"));
    EXPECT_FALSE(details == std::string_view("TESTTAG"));
}

// Boundary condition: substring should not match
TEST_F(StringTagDetailsTest_177, SubstringDoesNotMatch_177) {
    StringTagDetails details;
    details.val_ = "TestTag";
    EXPECT_FALSE(details == std::string_view("Test"));
    EXPECT_FALSE(details == std::string_view("Tag"));
}

// Boundary condition: superstring should not match
TEST_F(StringTagDetailsTest_177, SuperstringDoesNotMatch_177) {
    StringTagDetails details;
    details.val_ = "Test";
    EXPECT_FALSE(details == std::string_view("TestTag"));
}

// Normal operation: single character match
TEST_F(StringTagDetailsTest_177, SingleCharacterMatch_177) {
    StringTagDetails details;
    details.val_ = "X";
    EXPECT_TRUE(details == std::string_view("X"));
    EXPECT_FALSE(details == std::string_view("Y"));
}

// Boundary condition: strings with special characters
TEST_F(StringTagDetailsTest_177, SpecialCharacters_177) {
    StringTagDetails details;
    details.val_ = "tag/with-special_chars.123";
    EXPECT_TRUE(details == std::string_view("tag/with-special_chars.123"));
    EXPECT_FALSE(details == std::string_view("tag/with-special_chars.124"));
}

// Boundary condition: strings with spaces
TEST_F(StringTagDetailsTest_177, StringsWithSpaces_177) {
    StringTagDetails details;
    details.val_ = "hello world";
    EXPECT_TRUE(details == std::string_view("hello world"));
    EXPECT_FALSE(details == std::string_view("hello  world"));
    EXPECT_FALSE(details == std::string_view("helloworld"));
}

// Boundary condition: trailing/leading whitespace matters
TEST_F(StringTagDetailsTest_177, WhitespaceSensitivity_177) {
    StringTagDetails details;
    details.val_ = "test";
    EXPECT_FALSE(details == std::string_view(" test"));
    EXPECT_FALSE(details == std::string_view("test "));
    EXPECT_FALSE(details == std::string_view(" test "));
}

// Normal operation: long string comparison
TEST_F(StringTagDetailsTest_177, LongStringComparison_177) {
    std::string longStr(1000, 'a');
    StringTagDetails details;
    details.val_ = longStr;
    EXPECT_TRUE(details == std::string_view(longStr));

    std::string differentLongStr(1000, 'b');
    EXPECT_FALSE(details == std::string_view(differentLongStr));
}

// Verify that comparison with std::string works via implicit conversion to string_view
TEST_F(StringTagDetailsTest_177, ComparisonWithStdString_177) {
    StringTagDetails details;
    details.val_ = "hello";
    std::string key = "hello";
    EXPECT_TRUE(details == std::string_view(key));
}

// Boundary condition: null character in string_view
TEST_F(StringTagDetailsTest_177, StringWithEmbeddedNull_177) {
    StringTagDetails details;
    details.val_ = std::string_view("ab\0cd", 5);
    EXPECT_TRUE(details == std::string_view("ab\0cd", 5));
    EXPECT_FALSE(details == std::string_view("ab"));
}
