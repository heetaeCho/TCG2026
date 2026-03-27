#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class RegExTest_136 : public ::testing::Test {

protected:

    const RegEx& valueInJSONFlow = ValueInJSONFlow();

};



TEST_F(RegExTest_136, MatchesSingleCharacter_136) {

    EXPECT_TRUE(valueInJSONFlow.Matches(':'));

    EXPECT_FALSE(valueInJSONFlow.Matches('a'));

}



TEST_F(RegExTest_136, MatchesStringWithColon_136) {

    EXPECT_TRUE(valueInJSONFlow.Matches(":"));

    EXPECT_TRUE(valueInJSONFlow.Matches("abc:def"));

    EXPECT_FALSE(valueInJSONFlow.Matches("abcdef"));

}



TEST_F(RegExTest_136, MatchPositionSingleCharacter_136) {

    EXPECT_EQ(valueInJSONFlow.Match(":"), 1);

    EXPECT_EQ(valueInJSONFlow.Match("a"), -1);

}



TEST_F(RegExTest_136, MatchPositionInString_136) {

    EXPECT_EQ(valueInJSONFlow.Match("abc:def"), 3);

    EXPECT_EQ(valueInJSONFlow.Match(":abcdef"), 0);

    EXPECT_EQ(valueInJSONFlow.Match("abcdef:"), 6);

    EXPECT_EQ(valueInJSONFlow.Match("abcdef"), -1);

}
