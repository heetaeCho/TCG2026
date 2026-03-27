#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



// Test fixture for StringEqualsMatcher tests

class StringEqualsMatcherTest_225 : public ::testing::Test {

protected:

    // Utility function to check if the matcher matches a given string

    bool matches(const std::string& str, const StringEqualsMatcher& matcher) {

        return matcher.match(str).matched;

    }

};



// Test case to verify normal operation with case sensitive match

TEST_F(StringEqualsMatcherTest_225, CaseSensitiveMatch_225) {

    StringEqualsMatcher matcher = Equals("hello", CaseSensitivity::CaseSensitive);

    EXPECT_TRUE(matches("hello", matcher));

}



// Test case to verify normal operation with case insensitive match

TEST_F(StringEqualsMatcherTest_225, CaseInsensitiveMatch_225) {

    StringEqualsMatcher matcher = Equals("hello", CaseSensitivity::CaseInsensitive);

    EXPECT_TRUE(matches("HELLO", matcher));

}



// Test case to verify non-match with case sensitive comparison

TEST_F(StringEqualsMatcherTest_225, CaseSensitiveNonMatch_225) {

    StringEqualsMatcher matcher = Equals("hello", CaseSensitivity::CaseSensitive);

    EXPECT_FALSE(matches("HELLO", matcher));

}



// Test case to verify boundary condition of empty string match

TEST_F(StringEqualsMatcherTest_225, EmptyStringMatch_225) {

    StringEqualsMatcher matcher = Equals("", CaseSensitivity::CaseSensitive);

    EXPECT_TRUE(matches("", matcher));

}



// Test case to verify boundary condition of empty string non-match

TEST_F(StringEqualsMatcherTest_225, EmptyStringNonMatch_225) {

    StringEqualsMatcher matcher = Equals("hello", CaseSensitivity::CaseSensitive);

    EXPECT_FALSE(matches("", matcher));

}
