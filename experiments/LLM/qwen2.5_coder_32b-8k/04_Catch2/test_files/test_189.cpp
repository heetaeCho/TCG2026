#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class AllTrueMatcherTest_189 : public ::testing::Test {

protected:

    AllTrueMatcher matcher;

};



TEST_F(AllTrueMatcherTest_189, MatchesEmptyContainer_189) {

    std::vector<bool> emptyContainer;

    EXPECT_TRUE(matcher.match(emptyContainer));

}



TEST_F(AllTrueMatcherTest_189, MatchesAllTrueContainer_189) {

    std::vector<bool> allTrueContainer = {true, true, true};

    EXPECT_TRUE(matcher.match(allTrueContainer));

}



TEST_F(AllTrueMatcherTest_189, DoesNotMatchContainerWithFalse_189) {

    std::vector<bool> mixedContainer = {true, false, true};

    EXPECT_FALSE(matcher.match(mixedContainer));

}



TEST_F(AllTrueMatcherTest_189, DoesNotMatchSingleFalse_189) {

    std::vector<bool> singleFalseContainer = {false};

    EXPECT_FALSE(matcher.match(singleFalseContainer));

}
