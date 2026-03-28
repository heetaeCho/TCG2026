#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class HelpTest : public ::testing::Test {

protected:

    bool showHelpFlag;

    Help help;



    HelpTest() : showHelpFlag(false), help(showHelpFlag) {}

};



TEST_F(HelpTest_SetShowHelpFlagToTrue_1099, SetShowHelpFlagToTrue_1099) {

    help.parse("", {StringRef("--help")});

    EXPECT_TRUE(showHelpFlag);

}



TEST_F(HelpTest_SetShowHelpFlagToTrueWithShortOption_1099, SetShowHelpFlagToTrueWithShortOption_1099) {

    help.parse("", {StringRef("-h")});

    EXPECT_TRUE(showHelpFlag);

}



TEST_F(HelpTest_SetShowHelpFlagToTrueWithQuestionMark_1099, SetShowHelpFlagToTrueWithQuestionMark_1099) {

    help.parse("", {StringRef("-?")});

    EXPECT_TRUE(showHelpFlag);

}



TEST_F(HelpTest_NoOptionProvided_DoesNotSetShowHelpFlag_1099, NoOptionProvided_DoesNotSetShowHelpFlag_1099) {

    help.parse("", {});

    EXPECT_FALSE(showHelpFlag);

}



TEST_F(HelpTest_IsMatchWithValidLongOption_ReturnsTrue_1099, IsMatchWithValidLongOption_ReturnsTrue_1099) {

    EXPECT_TRUE(help.isMatch(StringRef("--help")));

}



TEST_F(HelpTest_IsMatchWithValidShortOption_ReturnsTrue_1099, IsMatchWithValidShortOption_ReturnsTrue_1099) {

    EXPECT_TRUE(help.isMatch(StringRef("-h")));

}



TEST_F(HelpTest_IsMatchWithValidQuestionMark_ReturnsTrue_1099, IsMatchWithValidQuestionMark_ReturnsTrue_1099) {

    EXPECT_TRUE(help.isMatch(StringRef("-?")));

}



TEST_F(HelpTest_IsMatchWithInvalidOption_ReturnsFalse_1099, IsMatchWithInvalidOption_ReturnsFalse_1099) {

    EXPECT_FALSE(help.isMatch(StringRef("--invalid")));

}



TEST_F(HelpTest_ParseWithEmptyTokens_DoesNotSetShowHelpFlag_1099, ParseWithEmptyTokens_DoesNotSetShowHelpFlag_1099) {

    help.parse("", {});

    EXPECT_FALSE(showHelpFlag);

}



TEST_F(HelpTest_Validate_ReturnsOkResult_1099, Validate_ReturnsOkResult_1099) {

    auto result = help.validate();

    EXPECT_TRUE(static_cast<bool>(result));

}
