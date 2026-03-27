#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class StringContainsMatcherTest_226 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StringContainsMatcherTest_226, ContainsSubstring_CaseSensitiveMatch_226) {

    std::string text = "Hello World";

    std::string substring = "World";

    StringContainsMatcher matcher = ContainsSubstring(substring, CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match(text));

}



TEST_F(StringContainsMatcherTest_226, ContainsSubstring_CaseInsensitiveMatch_226) {

    std::string text = "Hello World";

    std::string substring = "world";

    StringContainsMatcher matcher = ContainsSubstring(substring, CaseSensitive::No);

    EXPECT_TRUE(matcher.match(text));

}



TEST_F(StringContainsMatcherTest_226, ContainsSubstring_NoMatch_226) {

    std::string text = "Hello World";

    std::string substring = "Universe";

    StringContainsMatcher matcher = ContainsSubstring(substring, CaseSensitive::Yes);

    EXPECT_FALSE(matcher.match(text));

}



TEST_F(StringContainsMatcherTest_226, ContainsSubstring_EmptyText_226) {

    std::string text = "";

    std::string substring = "World";

    StringContainsMatcher matcher = ContainsSubstring(substring, CaseSensitive::Yes);

    EXPECT_FALSE(matcher.match(text));

}



TEST_F(StringContainsMatcherTest_226, ContainsSubstring_EmptySubstring_226) {

    std::string text = "Hello World";

    std::string substring = "";

    StringContainsMatcher matcher = ContainsSubstring(substring, CaseSensitive::Yes);

    EXPECT_TRUE(matcher.match(text));

}
