#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;

using namespace Catch::Matchers::Detail;



class MatchAnyOfTest_142 : public ::testing::Test {

protected:

    MatchAnyOf<int> match_any_of;

};



TEST_F(MatchAnyOfTest_142, DefaultConstructorInitializesEmpty_142) {

    EXPECT_FALSE(match_any_of.match(0));

}



TEST_F(MatchAnyOfTest_142, MoveConstructorPreservesState_142) {

    MatchAnyOf<int> original;

    MatchAnyOf<int> moved = CATCH_MOVE(original);

    EXPECT_FALSE(moved.match(0));

}



TEST_F(MatchAnyOfTest_142, DeletedCopyConstructor_142) {

    MatchAnyOf<int> original;

    // The following line should cause a compilation error if uncommented

    // MatchAnyOf<int> copied = original;

}



TEST_F(MatchAnyOfTest_142, MoveAssignmentPreservesState_142) {

    MatchAnyOf<int> original;

    MatchAnyOf<int> target;

    target = CATCH_MOVE(original);

    EXPECT_FALSE(target.match(0));

}



TEST_F(MatchAnyOfTest_142, DeletedCopyAssignment_142) {

    MatchAnyOf<int> original;

    MatchAnyOf<int> target;

    // The following line should cause a compilation error if uncommented

    // target = original;

}



TEST_F(MatchAnyOfTest_142, OperatorOrCombinesMatchers_142) {

    MatchAnyOf<int> matcher1;

    MatchAnyOf<int> matcher2;

    auto combined = matcher1 || CATCH_MOVE(matcher2);

    EXPECT_FALSE(combined.match(0));

}



TEST_F(MatchAnyOfTest_142, DescribeGeneratesDescription_142) {

    std::string description = match_any_of.describe();

    EXPECT_TRUE(description.size() > 0); // Assuming describe returns a non-empty string

}
