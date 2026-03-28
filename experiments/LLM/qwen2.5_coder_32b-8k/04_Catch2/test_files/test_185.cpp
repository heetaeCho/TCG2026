#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



// Mocking any dependencies if necessary (none in this case)

class MockDependency {

    // Define mocks here if there were any dependencies

};



// Test Fixture

class QuantifiersTest_185 : public ::testing::Test {

protected:

    // Setup and teardown can be defined here if needed

};



// Normal operation test cases

TEST_F(QuantifiersTest_185, AllMatchReturnsMatcher_185) {

    auto matcher = AllMatch(Equals(42));

    EXPECT_TRUE(matcher.match(std::vector<int>{42, 42, 42}));

}



// Boundary conditions test cases

TEST_F(QuantifiersTest_185, AllMatchEmptyContainer_185) {

    auto matcher = AllMatch(Equals(42));

    EXPECT_TRUE(matcher.match(std::vector<int>{})); // An empty container trivially satisfies the condition

}



TEST_F(QuantifiersTest_185, AllMatchSingleElementMatching_185) {

    auto matcher = AllMatch(Equals(42));

    EXPECT_TRUE(matcher.match(std::vector<int>{42}));

}



TEST_F(QuantifiersTest_185, AllMatchSingleElementNotMatching_185) {

    auto matcher = AllMatch(Equals(42));

    EXPECT_FALSE(matcher.match(std::vector<int>{99}));

}



// Exceptional or error cases (if observable through the interface)

// None in this case as the function is template-based and should not throw for typical usage



// Verification of external interactions

// None needed in this case as there are no external collaborators involved
