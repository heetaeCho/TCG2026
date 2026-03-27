#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class RegexpTest_535 : public ::testing::Test {

protected:

    RegexpTest_535() {}



    void SetUp() override {

        status.set_code(kRegexpSuccess);

    }



    RegexpStatus status;

};



TEST_F(RegexpTest_535, ParseSimpleLiteral_535) {

    std::string pattern = "abc";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseLiteralWithEscapedCharacter_535) {

    std::string pattern = "a\\bc";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseDotAndAnchors_535) {

    std::string pattern = "^a.b$";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseSimpleRepetition_535) {

    std::string pattern = "a*";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseCountedRepetition_535) {

    std::string pattern = "a{2,4}";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseCapturingGroup_535) {

    std::string pattern = "(abc)";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseAlternation_535) {

    std::string pattern = "a|b";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseConcatenation_535) {

    std::string pattern = "ab";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseEmptyString_535) {

    std::string pattern = "";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseLiteralWithPerlFlag_535) {

    std::string pattern = "\\pL";

    Regexp* result = Regexp::Parse(pattern, PerlClasses, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithMissingParenthesis_535) {

    std::string pattern = "(abc";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpMissingParen);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithUnexpectedParenthesis_535) {

    std::string pattern = "abc)";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpUnexpectedParen);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithBadEscape_535) {

    std::string pattern = "\\x";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadEscape);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithTrailingBackslash_535) {

    std::string pattern = "abc\\";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpTrailingBackslash);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithBadRepeatArgument_535) {

    std::string pattern = "a{2,1}";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpRepeatArgument);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParseInvalidPatternWithBadUTF8_535) {

    std::string pattern = "\xC2";

    Regexp* result = Regexp::Parse(pattern, NoParseFlags, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

    ASSERT_EQ(result, nullptr);

}



TEST_F(RegexpTest_535, ParsePatternWithLatin1Flag_535) {

    std::string pattern = "\xFF";

    Regexp* result = Regexp::Parse(pattern, Latin1, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_535, ParsePatternWithLiteralFlag_535) {

    std::string pattern = "(abc)";

    Regexp* result = Regexp::Parse(pattern, Literal, &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(result, nullptr);

    result->Decref();

}
