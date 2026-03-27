#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/yaml-cpp/src/exp.h"

#include "./TestProjects/yaml-cpp/src/regex_yaml.h"



using namespace YAML;

using namespace YAML::Exp;



class RegExTest_132 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(RegExTest_132, KeyMatchesQuestionMark_132) {

    const RegEx& keyRegex = Key();

    EXPECT_TRUE(keyRegex.Matches('?'));

}



TEST_F(RegExTest_132, KeyDoesNotMatchOtherCharacters_132) {

    const RegEx& keyRegex = Key();

    EXPECT_FALSE(keyRegex.Matches('a'));

    EXPECT_FALSE(keyRegex.Matches(' '));

    EXPECT_FALSE(keyRegex.Matches('\n'));

}



TEST_F(RegExTest_132, KeyMatchesEmptyString_132) {

    const RegEx& keyRegex = Key();

    EXPECT_FALSE(keyRegex.Matches(""));

}



TEST_F(RegExTest_132, KeyMatchesQuestionMarkFollowedByBlank_132) {

    const RegEx& keyRegex = Key();

    EXPECT_TRUE(keyRegex.Matches("? "));

    EXPECT_TRUE(keyRegex.Matches("?\n"));

}



TEST_F(RegExTest_132, KeyDoesNotMatchWithoutQuestionMark_132) {

    const RegEx& keyRegex = Key();

    EXPECT_FALSE(keyRegex.Matches(" a"));

    EXPECT_FALSE(keyRegex.Matches("\na"));

}



TEST_F(RegExTest_132, KeyDoesNotMatchExtraCharacters_132) {

    const RegEx& keyRegex = Key();

    EXPECT_FALSE(keyRegex.Matches("?a"));

    EXPECT_FALSE(keyRegex.Matches("?\n!"));

}
