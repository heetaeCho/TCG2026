#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class NoneTrueMatcherTest_191 : public ::testing::Test {

protected:

    NoneTrueMatcher noneTrueMatcher;

};



TEST_F(NoneTrueMatcherTest_191, MatchesEmptyContainer_191) {

    std::vector<bool> emptyVector;

    EXPECT_TRUE(noneTrueMatcher.match(emptyVector));

}



TEST_F(NoneTrueMatcherTest_191, MatchesContainerWithAllFalse_191) {

    std::vector<bool> falseVector = {false, false, false};

    EXPECT_TRUE(noneTrueMatcher.match(falseVector));

}



TEST_F(NoneTrueMatcherTest_191, DoesNotMatchContainerWithOneTrue_191) {

    std::vector<bool> mixedVector = {false, true, false};

    EXPECT_FALSE(noneTrueMatcher.match(mixedVector));

}



TEST_F(NoneTrueMatcherTest_191, DoesNotMatchContainerWithAllTrue_191) {

    std::vector<bool> trueVector = {true, true, true};

    EXPECT_FALSE(noneTrueMatcher.match(trueVector));

}
