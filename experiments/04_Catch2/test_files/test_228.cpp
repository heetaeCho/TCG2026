#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class StartsWithMatcherTest_228 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StartsWithMatcherTest_228, Match_ReturnsTrueForExactMatch_228) {

    std::string str = "Hello";

    StartsWithMatcher matcher = StartsWith(str);

    EXPECT_TRUE(matcher.match("Hello"));

}



TEST_F(StartsWithMatcherTest_228, Match_ReturnsTrueForPrefixMatch_228) {

    std::string str = "Hello";

    StartsWithMatcher matcher = StartsWith(str);

    EXPECT_TRUE(matcher.match("HelloWorld"));

}



TEST_F(StartsWithMatcherTest_228, Match_ReturnsFalseForNonMatchingString_228) {

    std::string str = "Hello";

    StartsWithMatcher matcher = StartsWith(str);

    EXPECT_FALSE(matcher.match("HiThere"));

}



TEST_F(StartsWithMatcherTest_228, Match_CaseSensitiveMatchReturnsTrue_228) {

    std::string str = "Hello";

    StartsWithMatcher matcher = StartsWith(str, CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match("Hello"));

}



TEST_F(StartsWithMatcherTest_228, Match_CaseInsensitiveMatchReturnsTrue_228) {

    std::string str = "hello";

    StartsWithMatcher matcher = StartsWith(str, CaseSensitive::No);

    EXPECT_TRUE(matcher.match("HELLOworld"));

}



TEST_F(StartsWithMatcherTest_228, Match_EmptyPrefixMatchesAnyString_228) {

    std::string str = "";

    StartsWithMatcher matcher = StartsWith(str);

    EXPECT_TRUE(matcher.match("HelloWorld"));

}



TEST_F(StartsWithMatcherTest_228, Match_LongerPrefixThanStringReturnsFalse_228) {

    std::string str = "HelloWorld!";

    StartsWithMatcher matcher = StartsWith(str);

    EXPECT_FALSE(matcher.match("HelloWorld"));

}



TEST_F(StartsWithMatcherTest_228, Describe_ReturnsExpectedDescription_228) {

    std::string str = "Hello";

    StartsWithMatcher matcher = StartsWith(str);

    std::string description;

    matcher.describe(description);

    EXPECT_EQ(description, "starts with \"Hello\"");

}



TEST_F(StartsWithMatcherTest_228, Describe_ReturnsExpectedDescription_CaseInsensitive_228) {

    std::string str = "hello";

    StartsWithMatcher matcher = StartsWith(str, CaseSensitive::No);

    std::string description;

    matcher.describe(description);

    EXPECT_EQ(description, "starts with \"hello\" (case insensitive)");

}
