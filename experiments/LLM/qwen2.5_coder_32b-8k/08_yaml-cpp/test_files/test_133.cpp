#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class KeyInFlowTest_133 : public ::testing::Test {

protected:

    const RegEx& keyInFlowRegex = KeyInFlow();

};



TEST_F(KeyInFlowTest_133, MatchesSingleQuestionMark_133) {

    EXPECT_TRUE(keyInFlowRegex.Matches('?'));

}



TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedBySpace_133) {

    EXPECT_TRUE(keyInFlowRegex.Matches("? "));

}



TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedByTab_133) {

    EXPECT_TRUE(keyInFlowRegex.Matches("?\t"));

}



TEST_F(KeyInFlowTest_133, DoesNotMatchSingleSpace_133) {

    EXPECT_FALSE(keyInFlowRegex.Matches(' '));

}



TEST_F(KeyInFlowTest_133, DoesNotMatchEmptyString_133) {

    EXPECT_FALSE(keyInFlowRegex.Matches(""));

}



TEST_F(KeyInFlowTest_133, DoesNotMatchQuestionMarkFollowedByNewline_133) {

    EXPECT_FALSE(keyInFlowRegex.Matches("?\n"));

}



TEST_F(KeyInFlowTest_133, DoesNotMatchJustTab_133) {

    EXPECT_FALSE(keyInFlowRegex.Matches("\t"));

}



TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedByCarriageReturn_133) {

    EXPECT_TRUE(keyInFlowRegex.Matches("?\r"));

}
