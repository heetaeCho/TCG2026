#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_244 : public ::testing::Test {

protected:

    RE2* re2_with_valid_pattern;

    RE2* re2_with_invalid_pattern;



    void SetUp() override {

        re2_with_valid_pattern = new RE2("abc");

        re2_with_invalid_pattern = new RE2("(");

    }



    void TearDown() override {

        delete re2_with_valid_pattern;

        delete re2_with_invalid_pattern;

    }

};



TEST_F(RE2Test_244, ProgramSize_ReturnsValidSizeForValidPattern_244) {

    EXPECT_GT(re2_with_valid_pattern->ProgramSize(), 0);

}



TEST_F(RE2Test_244, ProgramSize_ReturnsMinusOneForInvalidPattern_244) {

    EXPECT_EQ(re2_with_invalid_pattern->ProgramSize(), -1);

}



TEST_F(RE2Test_244, ReverseProgramSize_ReturnsValidSizeForValidPattern_244) {

    EXPECT_GT(re2_with_valid_pattern->ReverseProgramSize(), 0);

}



TEST_F(RE2Test_244, ReverseProgramSize_ReturnsMinusOneForInvalidPattern_244) {

    EXPECT_EQ(re2_with_invalid_pattern->ReverseProgramSize(), -1);

}



TEST_F(RE2Test_244, FullMatch_ReturnsTrueForExactMatch_244) {

    EXPECT_TRUE(RE2::FullMatch("abc", *re2_with_valid_pattern));

}



TEST_F(RE2Test_244, FullMatch_ReturnsFalseForNonExactMatch_244) {

    EXPECT_FALSE(RE2::FullMatch("abcd", *re2_with_valid_pattern));

}



TEST_F(RE2Test_244, PartialMatch_ReturnsTrueForPartialMatch_244) {

    EXPECT_TRUE(RE2::PartialMatch("abcde", *re2_with_valid_pattern));

}



TEST_F(RE2Test_244, PartialMatch_ReturnsFalseForNonPartialMatch_244) {

    EXPECT_FALSE(RE2::PartialMatch("def", *re2_with_valid_pattern));

}



TEST_F(RE2Test_244, Replace_ReplacesPatternWithRewriteString_244) {

    std::string input = "abc";

    RE2::Replace(&input, *re2_with_valid_pattern, "xyz");

    EXPECT_EQ(input, "xyz");

}



TEST_F(RE2Test_244, GlobalReplace_ReplacesAllOccurrencesOfPattern_244) {

    std::string input = "abcabc";

    int count = RE2::GlobalReplace(&input, *re2_with_valid_pattern, "xyz");

    EXPECT_EQ(input, "xyzxyz");

    EXPECT_EQ(count, 2);

}



TEST_F(RE2Test_244, Extract_ExtractsCapturingGroups_244) {

    RE2 re("a(b)c");

    std::string out;

    EXPECT_TRUE(re.Extract("abc", re, "$1", &out));

    EXPECT_EQ(out, "b");

}



TEST_F(RE2Test_244, Match_ReturnsTrueForMatchWithDefaultAnchors_244) {

    absl::string_view submatch[2];

    EXPECT_TRUE(re2_with_valid_pattern->Match("abc", 0, 3, RE2::ANCHOR_BOTH, submatch, 2));

}



TEST_F(RE2Test_244, Match_ReturnsFalseForNonMatchWithDefaultAnchors_244) {

    absl::string_view submatch[2];

    EXPECT_FALSE(re2_with_valid_pattern->Match("abcd", 0, 4, RE2::ANCHOR_BOTH, submatch, 2));

}



TEST_F(RE2Test_244, PossibleMatchRange_ReturnsTrueForPossibleMatches_244) {

    std::string min;

    std::string max;

    EXPECT_TRUE(re2_with_valid_pattern->PossibleMatchRange(&min, &max, 10));

}



TEST_F(RE2Test_244, NamedCapturingGroups_ReturnsValidMap_244) {

    RE2 re("(?<name>abc)");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 1);

    EXPECT_EQ(named_groups.at("name"), 0);

}



TEST_F(RE2Test_244, CapturingGroupNames_ReturnsValidMap_244) {

    RE2 re("(?<name>abc)");

    const std::map<int, std::string>& group_names = re.CapturingGroupNames();

    EXPECT_EQ(group_names.size(), 1);

    EXPECT_EQ(group_names.at(0), "name");

}
