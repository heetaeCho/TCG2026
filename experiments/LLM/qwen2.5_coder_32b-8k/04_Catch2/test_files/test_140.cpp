#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers::Detail;



class MatchAnyOfTest_140 : public ::testing::Test {

protected:

    MatchAnyOf<int> matchAnyOf;

};



TEST_F(MatchAnyOfTest_140, DefaultConstructorDoesNotCrash_140) {

    // Simply constructing the object should not result in any crashes

}



TEST_F(MatchAnyOfTest_140, MoveConstructorWorks_140) {

    MatchAnyOf<int> movedMatchAnyOf = std::move(matchAnyOf);

    // The move constructor should work without issues

}



TEST_F(MatchAnyOfTest_140, DeletedCopyConstructorPreventsCopying_140) {

    MatchAnyOf<int> anotherMatchAnyOf;

    EXPECT_FALSE((std::is_copy_constructible<MatchAnyOf<int>>::value));

}



TEST_F(MatchAnyOfTest_140, DeletedCopyAssignmentOperatorPreventsCopying_140) {

    MatchAnyOf<int> anotherMatchAnyOf;

    EXPECT_FALSE((std::is_copy_assignable<MatchAnyOf<int>>::value));

}



TEST_F(MatchAnyOfTest_140, MoveAssignmentWorks_140) {

    MatchAnyOf<int> movedMatchAnyOf;

    movedMatchAnyOf = std::move(matchAnyOf);

    // The move assignment operator should work without issues

}



TEST_F(MatchAnyOfTest_140, DescribeMethodReturnsNonEmptyString_140) {

    EXPECT_FALSE(matchAnyOf.describe().empty());

}



// Assuming match method is observable through some means (not provided in the snippet)

// TEST_F(MatchAnyOfTest_140, MatchMethodWorksForValidInput_140) {

//     // Setup and call match method with valid input

// }



// TEST_F(MatchAnyOfTest_140, MatchMethodFailsForInvalidInput_140) {

//     // Setup and call match method with invalid input

// }
