#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"

#include "./TestProjects/re2/re2/regexp.h"

#include "./TestProjects/re2/util/utf.h"



namespace re2 {



using ::testing::_;

using ::testing::Return;



class ParseEscapeTest : public ::testing::Test {

protected:

    absl::string_view input;

    Rune result;

    RegexpStatus status;

};



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashN_519) {

    input = "\\n";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\n');

}



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashR_519) {

    input = "\\r";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\r');

}



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashT_519) {

    input = "\\t";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\t');

}



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashA_519) {

    input = "\\a";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\a');

}



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashF_519) {

    input = "\\f";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\f');

}



TEST_F(ParseEscapeTest_519, NormalOperation_BackslashV_519) {

    input = "\\v";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '\v');

}



TEST_F(ParseEscapeTest_519, NormalOperation_HexadecimalEscape_519) {

    input = "\\x41";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, 'A');

}



TEST_F(ParseEscapeTest_519, NormalOperation_OctalEscape_519) {

    input = "\\061";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, '1');

}



TEST_F(ParseEscapeTest_519, NormalOperation_DecimalEscape_519) {

    input = "\\23";

    EXPECT_TRUE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(result, 023);

}



TEST_F(ParseEscapeTest_519, BoundaryCondition_EmptyString_519) {

    input = "";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(status.code(), kRegexpInternalError);

}



TEST_F(ParseEscapeTest_519, BoundaryCondition_TrailingBackslash_519) {

    input = "\\";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(status.code(), kRegexpTrailingBackslash);

}



TEST_F(ParseEscapeTest_519, BoundaryCondition_InvalidHexadecimalEscape_519) {

    input = "\\xZ1";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(ParseEscapeTest_519, BoundaryCondition_InvalidOctalEscape_519) {

    input = "\\8";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(ParseEscapeTest_519, ExceptionalCase_BadEscapeSequence_519) {

    input = "\\g";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runemax));

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(ParseEscapeTest_519, ExceptionalCase_ExceedRuneMaxHexadecimal_519) {

    input = "\\x{FFFFFFFF}";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runeself - 1));

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



TEST_F(ParseEscapeTest_519, ExceptionalCase_ExceedRuneMaxOctal_519) {

    input = "\\400";

    EXPECT_FALSE(ParseEscape(&input, &result, &status, Runeself - 1));

    EXPECT_EQ(status.code(), kRegexpBadEscape);

}



} // namespace re2
