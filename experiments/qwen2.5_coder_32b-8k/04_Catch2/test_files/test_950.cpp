#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch;

using namespace Matchers;



class ContainsElementMatcherTest_950 : public ::testing::Test {

protected:

    int desiredValue = 42;

    std::equal_to<int> equalityPredicate;

    ContainsElementMatcher<int, std::equal_to<int>> matcher;



    ContainsElementMatcherTest_950() : matcher(desiredValue, equalityPredicate) {}

};



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsTrueWhenElementExists_950) {

    std::vector<int> range = {1, 2, 3, 42, 5};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsFalseWhenElementDoesNotExist_950) {

    std::vector<int> range = {1, 2, 3, 5};

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsTrueForEmptyRangeWithDesiredValue_950) {

    std::vector<int> range;

    desiredValue = 42;

    ContainsElementMatcher<int, std::equal_to<int>> matcher(desiredValue, equalityPredicate);

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsFalseForEmptyRangeWithoutDesiredValue_950) {

    std::vector<int> range;

    desiredValue = 42;

    ContainsElementMatcher<int, std::equal_to<int>> matcher(desiredValue, equalityPredicate);

    EXPECT_FALSE(matcher.match(range));

}



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsTrueForSingleElementRangeWithDesiredValue_950) {

    std::vector<int> range = {42};

    EXPECT_TRUE(matcher.match(range));

}



TEST_F(ContainsElementMatcherTest_950, Match_ReturnsFalseForSingleElementRangeWithoutDesiredValue_950) {

    std::vector<int> range = {1};

    EXPECT_FALSE(matcher.match(range));

}
