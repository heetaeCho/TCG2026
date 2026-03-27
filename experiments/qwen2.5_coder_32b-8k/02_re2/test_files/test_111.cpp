#include <gtest/gtest.h>

#include "TestProjects/re2/re2/prog.h"



using namespace re2;



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_111, Matches_ReturnsTrueForInRangeCharacter_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_TRUE(inst.Matches('m'));

}



TEST_F(ProgInstTest_111, Matches_ReturnsFalseForOutOfRangeCharacter_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_FALSE(inst.Matches('Z'));

}



TEST_F(ProgInstTest_111, Matches_ReturnsTrueForInRangeUppercaseCharacterWithFoldCase_111) {

    inst.InitByteRange('a', 'z', 1, 0);

    EXPECT_TRUE(inst.Matches('M'));

}



TEST_F(ProgInstTest_111, Matches_ReturnsFalseForOutOfRangeUppercaseCharacterWithFoldCase_111) {

    inst.InitByteRange('a', 'z', 1, 0);

    EXPECT_FALSE(inst.Matches('{'));

}



TEST_F(ProgInstTest_111, Matches_BoundaryConditionLowerBound_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_TRUE(inst.Matches('a'));

}



TEST_F(ProgInstTest_111, Matches_BoundaryConditionUpperBound_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_TRUE(inst.Matches('z'));

}



TEST_F(ProgInstTest_111, Matches_BoundaryConditionBelowLowerBound_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_FALSE(inst.Matches('`'));

}



TEST_F(ProgInstTest_111, Matches_BoundaryConditionAboveUpperBound_111) {

    inst.InitByteRange('a', 'z', 0, 0);

    EXPECT_FALSE(inst.Matches('{'));

}
