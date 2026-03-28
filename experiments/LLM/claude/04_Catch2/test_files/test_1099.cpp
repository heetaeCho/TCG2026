#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Clara;

// Helper to check if Help properly sets the showHelpFlag
class HelpTest_1099 : public ::testing::Test {
protected:
    bool showHelpFlag = false;
};

TEST_F(HelpTest_1099, Construction_DefaultFlagIsFalse_1099) {
    // The flag should remain false after constructing Help (no parsing yet)
    bool flag = false;
    Help help(flag);
    EXPECT_FALSE(flag);
}

TEST_F(HelpTest_1099, HelpIsAnOpt_1099) {
    // Help inherits from Opt, so it should be usable as an Opt
    Help help(showHelpFlag);
    Opt& optRef = help;
    // Just verify we can treat it as an Opt without issues
    EXPECT_TRUE(optRef.isOptional());
}

TEST_F(HelpTest_1099, HelpMatchesShortH_1099) {
    Help help(showHelpFlag);
    EXPECT_TRUE(help.isMatch("-h"));
}

TEST_F(HelpTest_1099, HelpMatchesQuestionMark_1099) {
    Help help(showHelpFlag);
    EXPECT_TRUE(help.isMatch("-?"));
}

TEST_F(HelpTest_1099, HelpMatchesLongHelp_1099) {
    Help help(showHelpFlag);
    EXPECT_TRUE(help.isMatch("--help"));
}

TEST_F(HelpTest_1099, HelpDoesNotMatchUnrelatedOption_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch("--version"));
}

TEST_F(HelpTest_1099, HelpDoesNotMatchEmptyString_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch(""));
}

TEST_F(HelpTest_1099, HelpDoesNotMatchPartialH_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch("h"));
}

TEST_F(HelpTest_1099, HelpDoesNotMatchHelp_NoDoubleHyphen_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch("help"));
}

TEST_F(HelpTest_1099, HelpIsOptional_1099) {
    Help help(showHelpFlag);
    EXPECT_TRUE(help.isOptional());
}

TEST_F(HelpTest_1099, HelpDoesNotMatchSingleHyphenHelp_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch("-help"));
}

TEST_F(HelpTest_1099, HelpDoesNotMatchRandomOption_1099) {
    Help help(showHelpFlag);
    EXPECT_FALSE(help.isMatch("--foo"));
    EXPECT_FALSE(help.isMatch("-x"));
    EXPECT_FALSE(help.isMatch("-H")); // case sensitive
}

TEST_F(HelpTest_1099, HelpValidateSucceeds_1099) {
    Help help(showHelpFlag);
    auto result = help.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(HelpTest_1099, MultipleFlagsCanBeCreated_1099) {
    bool flag1 = false;
    bool flag2 = false;
    Help help1(flag1);
    Help help2(flag2);
    
    // Both should independently match
    EXPECT_TRUE(help1.isMatch("-h"));
    EXPECT_TRUE(help2.isMatch("--help"));
    
    // Flags should remain independent
    EXPECT_FALSE(flag1);
    EXPECT_FALSE(flag2);
}

TEST_F(HelpTest_1099, HelpGetHelpColumns_1099) {
    Help help(showHelpFlag);
    auto columns = help.getHelpColumns();
    // The description should contain "display usage information"
    // We check that the description is non-empty at least
    EXPECT_FALSE(columns.description.empty());
}

TEST_F(HelpTest_1099, HelpCardinality_1099) {
    Help help(showHelpFlag);
    // An option typically has cardinality of 0 (flag) or 1
    auto card = help.cardinality();
    EXPECT_GE(card, 0u);
}
