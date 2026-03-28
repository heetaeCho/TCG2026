#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.hpp"

#include <vector>



using namespace Catch::Matchers;



class NoneMatchMatcherTest_179 : public ::testing::Test {

protected:

    NoneMatchMatcherTest_179() {}

};



TEST_F(NoneMatchMatcherTest_179, EmptyRangeMatches_179) {

    std::vector<int> emptyVec;

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_TRUE(matcher.match(emptyVec));

}



TEST_F(NoneMatchMatcherTest_179, SingleNonMatchingElement_179) {

    std::vector<int> vec = {1};

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_TRUE(matcher.match(vec));

}



TEST_F(NoneMatchMatcherTest_179, MultipleNonMatchingElements_179) {

    std::vector<int> vec = {1, 2, 3};

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_TRUE(matcher.match(vec));

}



TEST_F(NoneMatchMatcherTest_179, SingleMatchingElement_179) {

    std::vector<int> vec = {42};

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_FALSE(matcher.match(vec));

}



TEST_F(NoneMatchMatcherTest_179, MultipleElementsWithOneMatching_179) {

    std::vector<int> vec = {1, 42, 3};

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_FALSE(matcher.match(vec));

}



TEST_F(NoneMatchMatcherTest_179, AllElementsMatching_179) {

    std::vector<int> vec = {42, 42, 42};

    NoneMatchMatcher<EqualMatcher<int>> matcher(Equals(42));

    EXPECT_FALSE(matcher.match(vec));

}
