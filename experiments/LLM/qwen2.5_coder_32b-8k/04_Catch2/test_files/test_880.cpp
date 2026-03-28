#include <gtest/gtest.h>

#include <string>



// Assuming the function escape_arg is in a header file named coverage-helper.h

#include "coverage-helper.h"



TEST(escape_arg_880, NoSpecialCharacters_880) {

    std::string input = "normal_string";

    std::string expected_output = "normal_string";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsSpace_880) {

    std::string input = "string with space";

    std::string expected_output = "\"string with space\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsTab_880) {

    std::string input = "string\twith\ttab";

    std::string expected_output = "\"string\twith\ttab\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsNewline_880) {

    std::string input = "string\nwith\nnewline";

    std::string expected_output = "\"string\nwith\nnewline\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsVerticalTab_880) {

    std::string input = "string\vwith\vtab";

    std::string expected_output = "\"string\vwith\vtab\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsDoubleQuote_880) {

    std::string input = "string\"with\"quote";

    std::string expected_output = "\"string\\\"with\\\"quote\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, ContainsBackslash_880) {

    std::string input = "string\\with\\backslash";

    std::string expected_output = "\"string\\\\with\\\\backslash\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, StartsAndEndsWithDoubleQuote_880) {

    std::string input = "\"start\"and\"end\"";

    std::string expected_output = "\"\\\"start\\\"and\\\"end\\\"\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, EmptyString_880) {

    std::string input = "";

    std::string expected_output = "";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, SingleBackslash_880) {

    std::string input = "\\";

    std::string expected_output = "\"\\\\\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}



TEST(escape_arg_880, DoubleBackslashesFollowedByQuote_880) {

    std::string input = "\\\\\"";

    std::string expected_output = "\"\\\\\\\"\"";

    EXPECT_EQ(expected_output, escape_arg(input));

}
