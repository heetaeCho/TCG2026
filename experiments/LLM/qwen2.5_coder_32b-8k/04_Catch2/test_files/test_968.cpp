#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



class EqualsMatcherTest_968 : public ::testing::Test {

protected:

    std::vector<int> comparator;

    std::vector<int> testVector1;

    std::vector<int> testVector2;

    std::vector<int> testVector3;



    void SetUp() override {

        comparator = {1, 2, 3};

        testVector1 = {1, 2, 3}; // matches comparator

        testVector2 = {4, 5, 6}; // does not match comparator

        testVector3 = {1, 2};    // size mismatch with comparator

    }

};



TEST_F(EqualsMatcherTest_968, MatchReturnsTrueForEqualVectors_968) {

    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    EXPECT_TRUE(matcher.match(testVector1));

}



TEST_F(EqualsMatcherTest_968, MatchReturnsFalseForNonEqualVectors_968) {

    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    EXPECT_FALSE(matcher.match(testVector2));

}



TEST_F(EqualsMatcherTest_968, MatchReturnsFalseForSizeMismatchedVectors_968) {

    EqualsMatcher<int, std::allocator<int>, std::allocator<int>> matcher(comparator);

    EXPECT_FALSE(matcher.match(testVector3));

}
