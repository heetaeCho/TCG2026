#include <gtest/gtest.h>

#include "re2/re2.h"



namespace {



class RE2Test_2 : public ::testing::Test {

protected:

    re2::RE2 regexSimplePattern;

    re2::RE2 regexComplexPattern;



    RE2Test_2() : regexSimplePattern("abc"), regexComplexPattern(R"(^(\d{3})-(\d{2})-(\d{4}))") {}

};



TEST_F(RE2Test_2, PatternReturnsCorrectValue_2) {

    EXPECT_EQ(regexSimplePattern.pattern(), "abc");

}



TEST_F(RE2Test_2, SimpleFullMatchSuccess_2) {

    EXPECT_TRUE(re2::RE2::FullMatch("abc", regexSimplePattern));

}



TEST_F(RE2Test_2, SimpleFullMatchFailure_2) {

    EXPECT_FALSE(re2::RE2::FullMatch("abcd", regexSimplePattern));

}



TEST_F(RE2Test_2, ComplexFullMatchSuccess_2) {

    std::string text = "123-45-6789";

    EXPECT_TRUE(re2::RE2::FullMatch(text, regexComplexPattern));

}



TEST_F(RE2Test_2, ComplexFullMatchFailure_2) {

    std::string text = "1234-56-7890"; // Invalid format

    EXPECT_FALSE(re2::RE2::FullMatch(text, regexComplexPattern));

}



TEST_F(RE2Test_2, PartialMatchSuccess_2) {

    std::string text = "xyzabcxyz";

    EXPECT_TRUE(re2::RE2::PartialMatch(text, regexSimplePattern));

}



TEST_F(RE2Test_2, PartialMatchFailure_2) {

    std::string text = "xyzabcd"; // No match for "abc"

    EXPECT_FALSE(re2::RE2::PartialMatch(text, regexComplexPattern));

}



TEST_F(RE2Test_2, GlobalReplaceSingleOccurrence_2) {

    std::string text = "abc";

    re2::RE2::GlobalReplace(&text, regexSimplePattern, "def");

    EXPECT_EQ(text, "def");

}



TEST_F(RE2Test_2, GlobalReplaceMultipleOccurrences_2) {

    std::string text = "abcabcabc";

    re2::RE2::GlobalReplace(&text, regexSimplePattern, "def");

    EXPECT_EQ(text, "defdefdef");

}



TEST_F(RE2Test_2, ExtractSuccess_2) {

    std::string text = "123-45-6789";

    std::string out;

    EXPECT_TRUE(re2::RE2::Extract(text, regexComplexPattern, R"(\1-\2-\3)", &out));

    EXPECT_EQ(out, "123-45-6789");

}



TEST_F(RE2Test_2, ExtractFailure_2) {

    std::string text = "invalid";

    std::string out;

    EXPECT_FALSE(re2::RE2::Extract(text, regexComplexPattern, R"(\1-\2-\3)", &out));

}



TEST_F(RE2Test_2, QuoteMetaBasicString_2) {

    std::string quoted = re2::RE2::QuoteMeta("abc");

    EXPECT_EQ(quoted, "abc");

}



TEST_F(RE2Test_2, QuoteMetaSpecialCharacters_2) {

    std::string quoted = re2::RE2::QuoteMeta("a.b[c]");

    EXPECT_EQ(quoted, "a\\.b\\[c\\]");

}



TEST_F(RE2Test_2, NumberOfCapturingGroupsSimplePattern_2) {

    EXPECT_EQ(regexSimplePattern.NumberOfCapturingGroups(), 0);

}



TEST_F(RE2Test_2, NumberOfCapturingGroupsComplexPattern_2) {

    EXPECT_EQ(regexComplexPattern.NumberOfCapturingGroups(), 3);

}



TEST_F(RE2Test_2, MatchAnchoredStartSuccess_2) {

    std::string text = "abc";

    absl::string_view submatch[1];

    EXPECT_TRUE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::ANCHOR_START, submatch, 1));

}



TEST_F(RE2Test_2, MatchAnchoredStartFailure_2) {

    std::string text = "xabc";

    absl::string_view submatch[1];

    EXPECT_FALSE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::ANCHOR_START, submatch, 1));

}



TEST_F(RE2Test_2, MatchAnchoredEndSuccess_2) {

    std::string text = "abc";

    absl::string_view submatch[1];

    EXPECT_TRUE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::ANCHOR_END, submatch, 1));

}



TEST_F(RE2Test_2, MatchAnchoredEndFailure_2) {

    std::string text = "abcx";

    absl::string_view submatch[1];

    EXPECT_FALSE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::ANCHOR_END, submatch, 1));

}



TEST_F(RE2Test_2, MatchUnanchoredSuccess_2) {

    std::string text = "xabcx";

    absl::string_view submatch[1];

    EXPECT_TRUE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::UNANCHORED, submatch, 1));

}



TEST_F(RE2Test_2, MatchUnanchoredFailure_2) {

    std::string text = "xyz";

    absl::string_view submatch[1];

    EXPECT_FALSE(regexSimplePattern.Match(text, 0, text.size(), re2::RE2::UNANCHORED, submatch, 1));

}



TEST_F(RE2Test_2, CheckRewriteStringValid_2) {

    std::string error;

    EXPECT_TRUE(regexComplexPattern.CheckRewriteString(R"(\1-\2-\3)", &error));

}



TEST_F(RE2Test_2, CheckRewriteStringInvalid_2) {

    std::string error;

    EXPECT_FALSE(regexComplexPattern.CheckRewriteString(R"(\4-\5-\6)", &error));

}



} // namespace
