#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_1 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



// Test for normal operation with a valid pattern

TEST_F(RE2Test_1, ValidPatternOk_1) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



// Test for boundary condition with an empty pattern

TEST_F(RE2Test_1, EmptyPatternOk_1) {

    RE2 re("");

    EXPECT_TRUE(re.ok());

}



// Test for exceptional case with a bad escape sequence in the pattern

TEST_F(RE2Test_1, BadEscapeSequenceNotOk_1) {

    RE2 re("abc\\");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with a bad character class in the pattern

TEST_F(RE2Test_1, BadCharClassNotOk_1) {

    RE2 re("[z-a]");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with a bad character range in the pattern

TEST_F(RE2Test_1, BadCharRangeNotOk_1) {

    RE2 re("[a-z-");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with missing bracket in the pattern

TEST_F(RE2Test_1, MissingBracketNotOk_1) {

    RE2 re("[abc");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with missing parenthesis in the pattern

TEST_F(RE2Test_1, MissingParenthesisNotOk_1) {

    RE2 re("(abc");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with unexpected parenthesis in the pattern

TEST_F(RE2Test_1, UnexpectedParenthesisNotOk_1) {

    RE2 re("abc)");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with trailing backslash in the pattern

TEST_F(RE2Test_1, TrailingBackslashNotOk_1) {

    RE2 re("abc\\");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with bad perl operator in the pattern

TEST_F(RE2Test_1, BadPerlOperatorNotOk_1) {

    RE2 re("a*b+");

    EXPECT_TRUE(re.ok()); // Perl operators are valid in RE2, this should be ok.

}



// Test for exceptional case with bad UTF-8 sequence in the pattern

TEST_F(RE2Test_1, BadUTF8SequenceNotOk_1) {

    const char* invalid_utf8 = "\xc3\x28";

    RE2 re(invalid_utf8);

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with bad named capture in the pattern

TEST_F(RE2Test_1, BadNamedCaptureNotOk_1) {

    RE2 re("(?P<name>abc");

    EXPECT_FALSE(re.ok());

}



// Test for exceptional case with pattern too large

TEST_F(RE2Test_1, PatternTooLargeNotOk_1) {

    std::string large_pattern(1000000, 'a');

    RE2 re(large_pattern);

    EXPECT_FALSE(re.ok());

}



// Test for normal operation of FullMatch function

TEST_F(RE2Test_1, FullMatchValidPattern_1) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::FullMatch("abc", re));

}



// Test for boundary condition of FullMatch function with empty pattern and string

TEST_F(RE2Test_1, FullMatchEmptyPatternAndString_1) {

    RE2 re("");

    EXPECT_TRUE(RE2::FullMatch("", re));

}



// Test for exceptional case of FullMatch function with invalid pattern

TEST_F(RE2Test_1, FullMatchInvalidPattern_1) {

    RE2 re("abc\\");

    EXPECT_FALSE(RE2::FullMatch("abc", re));

}



// Test for normal operation of PartialMatch function

TEST_F(RE2Test_1, PartialMatchValidPattern_1) {

    RE2 re("bc");

    EXPECT_TRUE(RE2::PartialMatch("abc", re));

}



// Test for boundary condition of PartialMatch function with empty pattern and string

TEST_F(RE2Test_1, PartialMatchEmptyPatternAndString_1) {

    RE2 re("");

    EXPECT_TRUE(RE2::PartialMatch("", re));

}



// Test for exceptional case of PartialMatch function with invalid pattern

TEST_F(RE2Test_1, PartialMatchInvalidPattern_1) {

    RE2 re("bc\\");

    EXPECT_FALSE(RE2::PartialMatch("abc", re));

}
