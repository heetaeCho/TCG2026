#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"

#include "re2/parse.cc"

#include "re2/regexp.h"

#include "re2/unicode_groups.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ParseCCNameTest_528 : public ::testing::Test {

protected:

    absl::string_view input;

    Regexp::ParseFlags parse_flags = 0;

    CharClassBuilder cc;

    RegexpStatus status;

};



TEST_F(ParseCCNameTest_528, NormalOperation_528) {

    input = "[:alnum:]";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseOk);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseCCNameTest_528, BoundaryCondition_EmptyString_528) {

    input = "";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseCCNameTest_528, BoundaryCondition_SingleBracket_528) {

    input = "[";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseCCNameTest_528, BoundaryCondition_OpeningBracketsOnly_528) {

    input = "[:";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseCCNameTest_528, BoundaryCondition_MissingClosingBrackets_528) {

    input = "[::alnum";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseNothing);

    EXPECT_TRUE(status.ok());

}



TEST_F(ParseCCNameTest_528, InvalidGroupName_528) {

    input = "[:invalid:]";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseError);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadCharRange);

    EXPECT_EQ(status.error_arg(), "[:invalid:]");

}



TEST_F(ParseCCNameTest_528, CorrectPrefixRemoval_528) {

    input = "[:alnum:]abc";

    EXPECT_EQ(ParseCCName(&input, parse_flags, &cc, &status), kParseOk);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(input, "abc");

}
