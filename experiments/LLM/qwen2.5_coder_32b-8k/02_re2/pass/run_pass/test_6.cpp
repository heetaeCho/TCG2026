#include <gtest/gtest.h>

#include "re2/re2.h"



class RE2Test : public ::testing::Test {

protected:

    re2::RE2* re2_valid;

    re2::RE2* re2_invalid;



    void SetUp() override {

        re2_valid = new re2::RE2("abc");

        re2_invalid = new re2::RE2("(");  // Invalid regex pattern

    }



    void TearDown() override {

        delete re2_valid;

        delete re2_invalid;

    }

};



TEST_F(RE2Test, Constructor_ValidPattern_6) {

    EXPECT_TRUE(re2_valid->ok());

}



TEST_F(RE2Test, Constructor_InvalidPattern_6) {

    EXPECT_FALSE(re2_invalid->ok());

}



TEST_F(RE2Test, FullMatch_ValidPatternAndText_6) {

    EXPECT_TRUE(re2::RE2::FullMatch("abc", *re2_valid));

}



TEST_F(RE2Test, FullMatch_ValidPatternButWrongText_6) {

    EXPECT_FALSE(re2::RE2::FullMatch("abcd", *re2_valid));

}



TEST_F(RE2Test, PartialMatch_ValidPatternAndPartialText_6) {

    EXPECT_TRUE(re2::RE2::PartialMatch("abcde", *re2_valid));

}



TEST_F(RE2Test, PartialMatch_ValidPatternButNoMatch_6) {

    EXPECT_FALSE(re2::RE2::PartialMatch("def", *re2_valid));

}



TEST_F(RE2Test, Consume_MatchingPrefix_6) {

    absl::string_view input = "abcde";

    EXPECT_TRUE(re2::RE2::Consume(&input, *re2_valid));

    EXPECT_EQ(input, "de");

}



TEST_F(RE2Test, Consume_NoMatchingPrefix_6) {

    absl::string_view input = "defabc";

    EXPECT_FALSE(re2::RE2::Consume(&input, *re2_valid));

    EXPECT_EQ(input, "defabc");

}



TEST_F(RE2Test, FindAndConsume_MatchingSubstring_6) {

    absl::string_view input = "xyzabcuvw";

    EXPECT_TRUE(re2::RE2::FindAndConsume(&input, *re2_valid));

    EXPECT_EQ(input, "uvw");

}



TEST_F(RE2Test, FindAndConsume_NoMatchingSubstring_6) {

    absl::string_view input = "xyzdefuvw";

    EXPECT_FALSE(re2::RE2::FindAndConsume(&input, *re2_valid));

    EXPECT_EQ(input, "xyzdefuvw");

}



TEST_F(RE2Test, Replace_SingleOccurrence_6) {

    std::string text = "abc";

    EXPECT_TRUE(re2::RE2::Replace(&text, *re2_valid, "123"));

    EXPECT_EQ(text, "123");

}



TEST_F(RE2Test, GlobalReplace_MultipleOccurrences_6) {

    re2::RE2* re2_multiple = new re2::RE2("a");

    std::string text = "aaaa";

    int count = re2::RE2::GlobalReplace(&text, *re2_multiple, "1");

    delete re2_multiple;

    EXPECT_EQ(count, 4);

    EXPECT_EQ(text, "1111");

}



TEST_F(RE2Test, Extract_Success_6) {

    std::string out;

    EXPECT_TRUE(re2::RE2::Extract("abc", *re2_valid, "$0", &out));

    EXPECT_EQ(out, "abc");

}



TEST_F(RE2Test, Extract_NoMatch_6) {

    std::string out;

    EXPECT_FALSE(re2::RE2::Extract("def", *re2_valid, "$0", &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2Test, QuoteMeta_SimpleText_6) {

    EXPECT_EQ(re2::RE2::QuoteMeta("abc.def"), "abc\\.def");

}



TEST_F(RE2Test, PossibleMatchRange_Unbounded_6) {

    std::string min;

    std::string max;

    EXPECT_TRUE(re2_valid->PossibleMatchRange(&min, &max, 0));

    EXPECT_EQ(min, "");

    EXPECT_EQ(max, "\xff\xff\xff\xff\xff\xff\xff\xff");

}



TEST_F(RE2Test, PossibleMatchRange_Bounded_6) {

    std::string min;

    std::string max;

    EXPECT_TRUE(re2_valid->PossibleMatchRange(&min, &max, 3));

    EXPECT_EQ(min, "abc");

    EXPECT_EQ(max, "abc");

}



TEST_F(RE2Test, Match_Success_6) {

    absl::string_view submatch[1];

    EXPECT_TRUE(re2_valid->Match("abc", 0, 3, re2::RE2::ANCHOR_BOTH, submatch, 1));

}



TEST_F(RE2Test, Match_NoSuccess_6) {

    absl::string_view submatch[1];

    EXPECT_FALSE(re2_valid->Match("def", 0, 3, re2::RE2::ANCHOR_BOTH, submatch, 1));

}



TEST_F(RE2Test, CheckRewriteString_Valid_6) {

    std::string error;

    EXPECT_TRUE(re2_valid->CheckRewriteString("abc$&def", &error));

    EXPECT_TRUE(error.empty());

}



TEST_F(RE2Test, CheckRewriteString_Invalid_6) {

    std::string error;

    EXPECT_FALSE(re2_valid->CheckRewriteString("abc\\k<1>def", &error));

    EXPECT_FALSE(error.empty());

}



TEST_F(RE2Test, MaxSubmatch_Valid_6) {

    EXPECT_EQ(re2_valid->MaxSubmatch("\\1"), 1);

}



TEST_F(RE2Test, Rewrite_Success_6) {

    absl::string_view submatch[1] = {"abc"};

    std::string out;

    EXPECT_TRUE(re2_valid->Rewrite(&out, "xyz$&uvw", submatch, 1));

    EXPECT_EQ(out, "xyzabcuvw");

}



TEST_F(RE2Test, Rewrite_NoMatch_6) {

    absl::string_view submatch[1] = {""};

    std::string out;

    EXPECT_TRUE(re2_valid->Rewrite(&out, "$&", submatch, 1));

    EXPECT_EQ(out, "");

}



TEST_F(RE2Test, NumberOfCapturingGroups_Zero_6) {

    EXPECT_EQ(re2_valid->NumberOfCapturingGroups(), 0);

}



TEST_F(RE2Test, Regexp_ReturnsNonNull_6) {

    EXPECT_NE(re2_valid->Regexp(), nullptr);

}
