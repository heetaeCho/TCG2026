#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



namespace YAML {

namespace Exp {



class ValueInFlowTest_135 : public ::testing::Test {

protected:

    const RegEx& value_in_flow = ValueInFlow();

};



TEST_F(ValueInFlowTest_135, MatchesColon_135) {

    EXPECT_TRUE(value_in_flow.Matches(':'));

}



TEST_F(ValueInFlowTest_135, MatchesComma_135) {

    EXPECT_TRUE(value_in_flow.Matches(','));

}



TEST_F(ValueInFlowTest_135, MatchesClosingBracket_135) {

    EXPECT_TRUE(value_in_flow.Matches(']'));

}



TEST_F(ValueInFlowTest_135, MatchesClosingCurlyBrace_135) {

    EXPECT_TRUE(value_in_flow.Matches('}'));

}



TEST_F(ValueInFlowTest_135, DoesNotMatchSpace_135) {

    EXPECT_FALSE(value_in_flow.Matches(' '));

}



TEST_F(ValueInFlowTest_135, DoesNotMatchTab_135) {

    EXPECT_FALSE(value_in_flow.Matches('\t'));

}



TEST_F(ValueInFlowTest_135, MatchesStringWithColon_135) {

    EXPECT_TRUE(value_in_flow.Matches(":"));

}



TEST_F(ValueInFlowTest_135, MatchesStringWithComma_135) {

    EXPECT_TRUE(value_in_flow.Matches(","));

}



TEST_F(ValueInFlowTest_135, MatchesStringWithClosingBracket_135) {

    EXPECT_TRUE(value_in_flow.Matches("]"));

}



TEST_F(ValueInFlowTest_135, MatchesStringWithClosingCurlyBrace_135) {

    EXPECT_TRUE(value_in_flow.Matches("}"));

}



TEST_F(ValueInFlowTest_135, DoesNotMatchStringWithSpace_135) {

    EXPECT_FALSE(value_in_flow.Matches(" "));

}



TEST_F(ValueInFlowTest_135, DoesNotMatchStringWithTab_135) {

    EXPECT_FALSE(value_in_flow.Matches("\t"));

}



TEST_F(ValueInFlowTest_135, MatchColonReturnsOne_135) {

    EXPECT_EQ(1, value_in_flow.Match(":"));

}



TEST_F(ValueInFlowTest_135, MatchCommaReturnsOne_135) {

    EXPECT_EQ(1, value_in_flow.Match(","));

}



TEST_F(ValueInFlowTest_135, MatchClosingBracketReturnsOne_135) {

    EXPECT_EQ(1, value_in_flow.Match("]"));

}



TEST_F(ValueInFlowTest_135, MatchClosingCurlyBraceReturnsOne_135) {

    EXPECT_EQ(1, value_in_flow.Match("}"));

}



TEST_F(ValueInFlowTest_135, MatchSpaceReturnsZero_135) {

    EXPECT_EQ(0, value_in_flow.Match(" "));

}



TEST_F(ValueInFlowTest_135, MatchTabReturnsZero_135) {

    EXPECT_EQ(0, value_in_flow.Match("\t"));

}



}  // namespace Exp

}  // namespace YAML
