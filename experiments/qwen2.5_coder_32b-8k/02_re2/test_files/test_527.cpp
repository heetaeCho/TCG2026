#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "parse.cc"

#include "regexp.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ParseUnicodeGroupTest_527 : public ::testing::Test {

protected:

    absl::string_view input;

    RegexpStatus status;

    CharClassBuilder cc;

};



TEST_F(ParseUnicodeGroupTest_527, NormalOperation_Han_527) {

    input = "\\p{Han}";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseOk);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, NormalOperation_Latin1_527) {

    input = "\\pL";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseOk);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, NegatedClass_Han_527) {

    input = "\\P{Han}";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseOk);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, NegatedClass_Latin1_527) {

    input = "\\PL";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseOk);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, BoundaryCondition_EmptyString_527) {

    input = "";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, BoundaryCondition_NoBackslash_527) {

    input = "p{Han}";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, BoundaryCondition_NoOpeningBrace_527) {

    input = "\\pHan";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseOk); // This should parse as a single character 'H', 'a', 'n'

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, BoundaryCondition_NoClosingBrace_527) {

    input = "\\p{Han";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseError);

    EXPECT_FALSE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, BoundaryCondition_InvalidUTF8_527) {

    input = "\\p{H\xF1n}"; // Invalid UTF-8

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseError);

    EXPECT_FALSE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, ExceptionalCase_NoUnicodeGroupsFlag_527) {

    input = "\\p{Han}";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::NoParseFlags, &cc, &status);

    EXPECT_EQ(result, kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseUnicodeGroupTest_527, ExceptionalCase_UnrecognizedGroupName_527) {

    input = "\\p{Unknown}";

    ParseStatus result = ParseUnicodeGroup(&input, Regexp::UnicodeGroups, &cc, &status);

    EXPECT_EQ(result, kParseError);

    EXPECT_FALSE(status.ok());

}
