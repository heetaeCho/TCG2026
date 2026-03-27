#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_405 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_405, SearchNFA_MatchesPattern_405) {

    absl::string_view text = "test";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches "test"

    bool result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);

}



TEST_F(ProgTest_405, SearchNFA_NoMatchPattern_405) {

    absl::string_view text = "example";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that does not match "example"

    bool result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchDFA_MatchesPattern_405) {

    absl::string_view text = "test";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match0;

    bool failed;

    SparseSet matches;



    // Assuming a pattern is set that matches "test"

    bool result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

    EXPECT_TRUE(result);

    EXPECT_EQ(match0, text);

}



TEST_F(ProgTest_405, SearchDFA_NoMatchPattern_405) {

    absl::string_view text = "example";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match0;

    bool failed;

    SparseSet matches;



    // Assuming a pattern is set that does not match "example"

    bool result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchOnePass_MatchesPattern_405) {

    absl::string_view text = "test";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches "test"

    bool result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);

}



TEST_F(ProgTest_405, SearchOnePass_NoMatchPattern_405) {

    absl::string_view text = "example";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that does not match "example"

    bool result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchBitState_MatchesPattern_405) {

    absl::string_view text = "test";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches "test"

    bool result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);

}



TEST_F(ProgTest_405, SearchBitState_NoMatchPattern_405) {

    absl::string_view text = "example";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that does not match "example"

    bool result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, PossibleMatchRange_ValidRange_405) {

    std::string min;

    std::string max;

    int maxlen = 10;



    // Assuming a pattern is set that can match a valid range

    bool result = prog->PossibleMatchRange(&min, &max, maxlen);

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_405, PossibleMatchRange_NoValidRange_405) {

    std::string min;

    std::string max;

    int maxlen = 1;



    // Assuming a pattern is set that cannot match any range within maxlen

    bool result = prog->PossibleMatchRange(&min, &max, maxlen);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchNFA_EmptyText_405) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches empty string

    bool result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);



    // Assuming a pattern is set that does not match empty string

    prog->ConfigurePrefixAccel("test", false);

    result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchDFA_EmptyText_405) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match0;

    bool failed;

    SparseSet matches;



    // Assuming a pattern is set that matches empty string

    bool result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

    EXPECT_TRUE(result);

    EXPECT_EQ(match0, text);



    // Assuming a pattern is set that does not match empty string

    prog->ConfigurePrefixAccel("test", false);

    result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchOnePass_EmptyText_405) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches empty string

    bool result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);



    // Assuming a pattern is set that does not match empty string

    prog->ConfigurePrefixAccel("test", false);

    result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_405, SearchBitState_EmptyText_405) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NORM;

    absl::string_view match;

    int nmatch = 1;



    // Assuming a pattern is set that matches empty string

    bool result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

    EXPECT_TRUE(result);

    EXPECT_EQ(match, text);



    // Assuming a pattern is set that does not match empty string

    prog->ConfigurePrefixAccel("test", false);

    result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

    EXPECT_FALSE(result);

}
