#include <gtest/gtest.h>

#include "re2/re2/parse.cc"

#include "re2/util/utf.h"



namespace re2 {



class StringViewToRuneTest_515 : public ::testing::Test {

protected:

    absl::string_view input;

    RegexpStatus status;

};



TEST_F(StringViewToRuneTest_515, NormalOperationSingleByte_515) {

    Rune r = 0;

    input = "a";

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(r, 'a');

    EXPECT_TRUE(input.empty());

    EXPECT_TRUE(status.ok());

}



TEST_F(StringViewToRuneTest_515, NormalOperationMultiByte_515) {

    Rune r = 0;

    input = "😊"; // U+1F60A

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(r, 0x1F60A);

    EXPECT_TRUE(input.empty());

    EXPECT_TRUE(status.ok());

}



TEST_F(StringViewToRuneTest_515, BoundaryConditionEmptyString_515) {

    Rune r = 0;

    input = "";

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, -1);

    EXPECT_EQ(r, 0);

    EXPECT_TRUE(input.empty());

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(StringViewToRuneTest_515, BoundaryConditionSingleByteOverlong_515) {

    Rune r = 0;

    input = "\xC2\xA9"; // Overlong ASCII character '©'

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, -1);

    EXPECT_EQ(r, 0);

    EXPECT_TRUE(input.empty());

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(StringViewToRuneTest_515, BoundaryConditionIncompleteMultiByte_515) {

    Rune r = 0;

    input = "\xF4\x90\x80"; // Incomplete 4-byte sequence

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, -1);

    EXPECT_EQ(r, 0);

    EXPECT_TRUE(input.empty());

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(StringViewToRuneTest_515, ExceptionalCaseInvalidUTF8_515) {

    Rune r = 0;

    input = "\xFF"; // Invalid UTF-8 byte

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, -1);

    EXPECT_EQ(r, 0);

    EXPECT_TRUE(input.empty());

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(StringViewToRuneTest_515, ExceptionalCaseRuneError_515) {

    Rune r = 0;

    input = "\xF4\x90\x80\xB3"; // Out of range UTF-8 sequence

    int result = StringViewToRune(&r, &input, &status);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(r, Runeerror);

    EXPECT_TRUE(input.empty());

    EXPECT_TRUE(status.ok());

}



} // namespace re2
