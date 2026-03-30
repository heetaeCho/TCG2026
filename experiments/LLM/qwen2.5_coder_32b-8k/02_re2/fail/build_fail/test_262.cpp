#include <gtest/gtest.h>

#include "re2/re2.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RE2Test : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string valid_pattern = R"(abc)";

    std::string invalid_pattern = R"((?<!))"; // Invalid regex pattern



    RE2 valid_re(valid_pattern);

    RE2 invalid_re(invalid_pattern);

};



// Test normal operation with a valid pattern

TEST_F(RE2Test, MatchValidPattern_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_TRUE(valid_re.Match(text, 0, text.size(), UNANCHORED, &submatch, 1));

}



// Test boundary conditions with startpos and endpos

TEST_F(RE2Test, MatchBoundaryConditions_StartEndPos_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_TRUE(valid_re.Match(text, 0, 3, UNANCHORED, &submatch, 1));

    EXPECT_FALSE(valid_re.Match(text, 1, 3, ANCHOR_START, &submatch, 1));

}



// Test invalid pattern

TEST_F(RE2Test, MatchInvalidPattern_Error_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_FALSE(invalid_re.Match(text, 0, text.size(), UNANCHORED, &submatch, 1));

}



// Test startpos greater than endpos

TEST_F(RE2Test, MatchInvalidStartEndPos_Error_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_FALSE(valid_re.Match(text, 3, 0, UNANCHORED, &submatch, 1));

}



// Test endpos greater than text size

TEST_F(RE2Test, MatchEndPosGreaterThanTextSize_Error_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_FALSE(valid_re.Match(text, 0, 4, UNANCHORED, &submatch, 1));

}



// Test ANCHOR_BOTH

TEST_F(RE2Test, MatchAnchorBoth_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_TRUE(valid_re.Match(text, 0, 3, ANCHOR_BOTH, &submatch, 1));

}



// Test ANCHOR_START

TEST_F(RE2Test, MatchAnchorStart_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_TRUE(valid_re.Match(text, 0, 3, ANCHOR_START, &submatch, 1));

}



// Test nsubmatch equals to zero

TEST_F(RE2Test, MatchNsubmatchZero_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch;

    EXPECT_TRUE(valid_re.Match(text, 0, 3, UNANCHORED, nullptr, 0));

}



// Test nsubmatch greater than number of capturing groups

TEST_F(RE2Test, MatchNsubmatchGreaterThanCapturingGroups_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch[5];

    EXPECT_TRUE(valid_re.Match(text, 0, 3, UNANCHORED, submatch, 5));

}



// Test submatch array

TEST_F(RE2Test, MatchSubmatchArray_Normal_262) {

    absl::string_view text("abc");

    absl::string_view submatch[1];

    EXPECT_TRUE(valid_re.Match(text, 0, 3, UNANCHORED, submatch, 1));

    EXPECT_EQ(submatch[0], "abc");

}
