#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



class UnorderedEqualsMatcherTest_976 : public ::testing::Test {

protected:

    std::vector<int> targetVector = {1, 2, 3};

};



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithSameElementsInDifferentOrder_976) {

    std::vector<int> testVector = {3, 2, 1};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithDifferentElements_976) {

    std::vector<int> testVector = {4, 5, 6};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithSubsetOfElements_976) {

    std::vector<int> testVector = {1, 2};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithSupersetOfElements_976) {

    std::vector<int> testVector = {1, 2, 3, 4};

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithEmptyTargetAndTestVectors_976) {

    std::vector<int> emptyVector;

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(emptyVector);

    EXPECT_TRUE(matcher.match(emptyVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithEmptyTargetAndNonEmptyTestVectors_976) {

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher({});

    EXPECT_FALSE(matcher.match({1, 2, 3}));

}



TEST_F(UnorderedEqualsMatcherTest_976, MatchWithNonEmptyTargetAndEmptyTestVectors_976) {

    std::vector<int> testVector;

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(UnorderedEqualsMatcherTest_976, DescribeOutputsCorrectString_976) {

    UnorderedEqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(targetVector);

    EXPECT_EQ("UnorderedEquals: {1, 2, 3}", matcher.describe());

}
