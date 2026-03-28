#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MatchAnyOfTest : public ::testing::Test {

protected:

    MatchAnyOf<int> matchAnyOf;

};



TEST_F(MatchAnyOfTest_141, DefaultConstructorInitializesEmpty_141) {

    EXPECT_FALSE(matchAnyOf.match(0));

}



TEST_F(MatchAnyOfTest_141, MoveConstructorPreservesMatchers_141) {

    MatchAnyOf<int> original;

    original.m_matchers.push_back(new Catch::Matchers::EqualsMatcher<int>(5));



    MatchAnyOf<int> moved = CATCH_MOVE(original);

    EXPECT_TRUE(moved.match(5));

}



TEST_F(MatchAnyOfTest_141, MoveAssignmentPreservesMatchers_141) {

    MatchAnyOf<int> original;

    original.m_matchers.push_back(new Catch::Matchers::EqualsMatcher<int>(7));



    MatchAnyOf<int> moved;

    moved = CATCH_MOVE(original);

    EXPECT_TRUE(moved.match(7));

}



TEST_F(MatchAnyOfTest_141, DeletedCopyConstructor_141) {

    MatchAnyOf<int> original;

    // This should not compile if copy constructor is deleted

    // MatchAnyOf<int> copied = original;

}



TEST_F(MatchAnyOfTest_141, DeletedCopyAssignment_141) {

    MatchAnyOf<int> original;

    MatchAnyOf<int> another;

    // This should not compile if copy assignment is deleted

    // another = original;

}



TEST_F(MatchAnyOfTest_141, OrOperatorAddsMatcher_141) {

    matchAnyOf || Catch::Matchers::EqualsMatcher<int>(3);

    EXPECT_TRUE(matchAnyOf.match(3));

}



TEST_F(MatchAnyOfTest_141, MultipleOrOperatorsAddMultipleMatchers_141) {

    matchAnyOf || Catch::Matchers::EqualsMatcher<int>(2);

    matchAnyOf || Catch::Matchers::EqualsMatcher<int>(5);

    EXPECT_TRUE(matchAnyOf.match(2));

    EXPECT_TRUE(matchAnyOf.match(5));

}



TEST_F(MatchAnyOfTest_141, MatchFailsForNonMatchingValues_141) {

    matchAnyOf || Catch::Matchers::EqualsMatcher<int>(8);

    EXPECT_FALSE(matchAnyOf.match(9));

}
