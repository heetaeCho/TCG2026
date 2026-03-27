#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class EndsWithMatcherTest_222 : public ::testing::Test {

protected:

    CasedString caseSensitiveComparator;

    CasedString caseInsensitiveComparator;



    void SetUp() override {

        caseSensitiveComparator = CasedString("World", CaseSensitive::Yes);

        caseInsensitiveComparator = CasedString("world", CaseSensitive::No);

    }

};



TEST_F(EndsWithMatcherTest_222, Match_ReturnsTrueForExactMatch_222) {

    EndsWithMatcher matcher(caseSensitiveComparator);

    EXPECT_TRUE(matcher.match("Hello World"));

}



TEST_F(EndsWithMatcherTest_222, Match_ReturnsFalseForNonMatchingString_222) {

    EndsWithMatcher matcher(caseSensitiveComparator);

    EXPECT_FALSE(matcher.match("Hello World!"));

}



TEST_F(EndsWithMatcherTest_222, Match_CaseInsensitiveMatch_222) {

    EndsWithMatcher matcher(caseInsensitiveComparator);

    EXPECT_TRUE(matcher.match("Hello WORLD"));

}



TEST_F(EndsWithMatcherTest_222, Match_EmptySourceString_ReturnsFalse_222) {

    EndsWithMatcher matcher(caseSensitiveComparator);

    EXPECT_FALSE(matcher.match(""));

}



TEST_F(EndsWithMatcherTest_222, Match_EmptyPattern_ReturnsTrue_222) {

    CasedString emptyComparator("", CaseSensitive::Yes);

    EndsWithMatcher matcher(emptyComparator);

    EXPECT_TRUE(matcher.match("Hello World"));

}
