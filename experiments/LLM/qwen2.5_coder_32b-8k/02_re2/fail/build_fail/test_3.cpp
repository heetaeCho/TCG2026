#include <gtest/gtest.h>

#include "re2/re2.h"

#include <string>



namespace {



class RE2Test : public ::testing::Test {

protected:

    re2::RE2* valid_re2;

    re2::RE2* invalid_re2;



    void SetUp() override {

        valid_re2 = new re2::RE2("abc");

        invalid_re2 = new re2::RE2("(abc");

    }



    void TearDown() override {

        delete valid_re2;

        delete invalid_re2;

    }

};



TEST_F(RE2Test_3, ValidPattern_IsOk_3) {

    EXPECT_TRUE(valid_re2->ok());

}



TEST_F(RE2Test_3, InvalidPattern_NotOk_3) {

    EXPECT_FALSE(invalid_re2->ok());

}



TEST_F(RE2Test_3, ValidPattern_ErrorIsEmpty_3) {

    EXPECT_EQ(valid_re2->error(), "");

}



TEST_F(RE2Test_3, InvalidPattern_ErrorIsNotEmpty_3) {

    EXPECT_NE(invalid_re2->error(), "");

}



TEST_F(RE2Test_3, Pattern_ReturnsCorrectValue_3) {

    EXPECT_EQ(valid_re2->pattern(), "abc");

}



TEST_F(RE2Test_3, FullMatch_ValidPatternAndText_ReturnsTrue_3) {

    EXPECT_TRUE(re2::RE2::FullMatch("abc", *valid_re2));

}



TEST_F(RE2Test_3, FullMatch_ValidPatternAndInvalidText_ReturnsFalse_3) {

    EXPECT_FALSE(re2::RE2::FullMatch("abcd", *valid_re2));

}



TEST_F(RE2Test_3, PartialMatch_ValidPatternAndPartialText_ReturnsTrue_3) {

    EXPECT_TRUE(re2::RE2::PartialMatch("abcde", *valid_re2));

}



TEST_F(RE2Test_3, PartialMatch_ValidPatternAndNonMatchingText_ReturnsFalse_3) {

    EXPECT_FALSE(re2::RE2::PartialMatch("def", *valid_re2));

}



TEST_F(RE2Test_3, Consume_MatchingText_ReturnsTrueAndUpdateInput_3) {

    std::string input = "abcde";

    EXPECT_TRUE(re2::RE2::Consume(&input, *valid_re2));

    EXPECT_EQ(input, "de");

}



TEST_F(RE2Test_3, Consume_NonMatchingText_ReturnsFalseAndDoNotUpdateInput_3) {

    std::string input = "def";

    EXPECT_FALSE(re2::RE2::Consume(&input, *valid_re2));

    EXPECT_EQ(input, "def");

}



TEST_F(RE2Test_3, FindAndConsume_MatchingSubstring_ReturnsTrueAndUpdateInput_3) {

    std::string input = "1abc2";

    EXPECT_TRUE(re2::RE2::FindAndConsume(&input, *valid_re2));

    EXPECT_EQ(input, "2");

}



TEST_F(RE2Test_3, FindAndConsume_NoMatchingSubstring_ReturnsFalseAndDoNotUpdateInput_3) {

    std::string input = "1def2";

    EXPECT_FALSE(re2::RE2::FindAndConsume(&input, *valid_re2));

    EXPECT_EQ(input, "1def2");

}



TEST_F(RE2Test_3, Replace_Substring_ReplacesCorrectly_3) {

    std::string str = "abcde";

    re2::RE2::Replace(&str, *valid_re2, "xyz");

    EXPECT_EQ(str, "xyzde");

}



TEST_F(RE2Test_3, GlobalReplace_AllOccurrencesReplaced_3) {

    std::string str = "abcabc";

    int count = re2::RE2::GlobalReplace(&str, *valid_re2, "xyz");

    EXPECT_EQ(str, "xyzxyz");

    EXPECT_EQ(count, 2);

}



TEST_F(RE2Test_3, Extract_ExtractsCorrectly_3) {

    std::string text = "abc";

    std::string out;

    EXPECT_TRUE(re2::RE2::Extract(text, *valid_re2, "$0", &out));

    EXPECT_EQ(out, "abc");

}



TEST_F(RE2Test_3, NumberOfCapturingGroups_ReturnsCorrectValue_3) {

    EXPECT_EQ(valid_re2->NumberOfCapturingGroups(), 0);

}



TEST_F(RE2Test_3, QuoteMeta_EscapesSpecialCharacters_3) {

    std::string quoted = re2::RE2::QuoteMeta("abc.$|");

    EXPECT_EQ(quoted, "abc\\.\\$\\|");

}



} // namespace
