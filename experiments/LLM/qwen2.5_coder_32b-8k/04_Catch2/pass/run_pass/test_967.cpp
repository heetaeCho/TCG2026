#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;

using ::testing::Return;



class ContainsMatcherTest_967 : public ::testing::Test {

protected:

    std::vector<int> comparator;

    ContainsMatcher<int, std::allocator<int>, std::allocator<int>>* matcher;



    void SetUp() override {

        comparator = {1, 2, 3};

        matcher = new ContainsMatcher<int, std::allocator<int>, std::allocator<int>>(comparator);

    }



    void TearDown() override {

        delete matcher;

    }

};



TEST_F(ContainsMatcherTest_967, Match_ReturnsTrueForContainedElement_967) {

    std::vector<int> testVector = {4, 2, 5};

    EXPECT_TRUE(matcher->match(testVector));

}



TEST_F(ContainsMatcherTest_967, Match_ReturnsFalseForNonContainedElement_967) {

    std::vector<int> testVector = {4, 5, 6};

    EXPECT_FALSE(matcher->match(testVector));

}



TEST_F(ContainsMatcherTest_967, Describe_ReturnsCorrectDescription_967) {

    EXPECT_EQ(matcher->describe(), "Contains: {   1,\n  2,\n  3 }");

}



TEST_F(ContainsMatcherTest_967, Match_BoundaryCondition_EmptyVector_967) {

    std::vector<int> testVector = {};

    EXPECT_FALSE(matcher->match(testVector));

}



TEST_F(ContainsMatcherTest_967, Match_BoundaryCondition_SingleElementMatch_967) {

    std::vector<int> testVector = {1};

    EXPECT_TRUE(matcher->match(testVector));

}



TEST_F(ContainsMatcherTest_967, Match_BoundaryCondition_SingleElementNonMatch_967) {

    std::vector<int> testVector = {4};

    EXPECT_FALSE(matcher->match(testVector));

}
