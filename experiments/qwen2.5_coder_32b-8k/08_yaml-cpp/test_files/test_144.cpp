#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



class RegExTest_144 : public ::testing::Test {

protected:

    YAML::Exp::RegEx& plainScalarInFlow = const_cast<YAML::Exp::RegEx&>(YAML::Exp::PlainScalarInFlow());

};



TEST_F(RegExTest_144, MatchesValidCharacter_144) {

    EXPECT_TRUE(plainScalarInFlow.Matches('a'));

}



TEST_F(RegExTest_144, MatchesValidString_144) {

    EXPECT_TRUE(plainScalarInFlow.Matches("valid-string"));

}



TEST_F(RegExTest_144, MatchesEmptyString_144) {

    EXPECT_TRUE(plainScalarInFlow.Matches(""));

}



TEST_F(RegExTest_144, DoesNotMatchBlankOrBreak_144) {

    EXPECT_FALSE(plainScalarInFlow.Matches(' '));

    EXPECT_FALSE(plainScalarInFlow.Matches('\n'));

}



TEST_F(RegExTest_144, DoesNotMatchSpecialCharacters_144) {

    std::string specialChars = "?,[]{}#&*!|>\"%@`";

    for (char ch : specialChars) {

        EXPECT_FALSE(plainScalarInFlow.Matches(ch));

    }

}



TEST_F(RegExTest_144, DoesNotMatchHyphenColonFollowedByBlankOrBreak_144) {

    EXPECT_FALSE(plainScalarInFlow.Matches("-: "));

    EXPECT_FALSE(plainScalarInFlow.Matches("-:\n"));

}



TEST_F(RegExTest_144, MatchesHyphenColonWithoutFollowingCharacters_144) {

    EXPECT_TRUE(plainScalarInFlow.Matches("-:"));

}
