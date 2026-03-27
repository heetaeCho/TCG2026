#include <gtest/gtest.h>

#include "re2/prog.h"

#include "absl/strings/string_view.h"



namespace re2 {

using ::testing::Test;



class ProgTest_578 : public Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_578, SearchNFANormalOperation_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFANoMatch_578) {

    absl::string_view text = "world";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionEmptyText_578) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionFullMatch_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionFullMatchNoMatch_578) {

    absl::string_view text = "hell";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionNoMatchEmptyText_578) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_578, SearchNFALongestMatch_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kLongestMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFAManyMatch_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kManyMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionNMATCHZero_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view* match = nullptr;

    int nmatch = 0;



    bool result = prog.SearchNFA(text, context, anchor, kind, match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionNMATCHNegative_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view* match = nullptr;

    int nmatch = -1;



    bool result = prog.SearchNFA(text, context, anchor, kind, match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_FALSE(result); // This should fail or be undefined behavior

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionAnchorUnanchored_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionAnchorAnchored_578) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionAnchorUnanchoredNoMatch_578) {

    absl::string_view text = "ohello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "^hello"

    EXPECT_FALSE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionAnchorAnchoredNoMatch_578) {

    absl::string_view text = "ohello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match;

    int nmatch = 1;



    bool result = prog.SearchNFA(text, context, anchor, kind, &match, nmatch);

    // Assuming the regex is configured to match "^hello"

    EXPECT_TRUE(result);

}



TEST_F(ProgTest_578, SearchNFABoundaryConditionNMATCHGreaterThanOne_578) {

    absl::string_view text = "hello world";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[2];

    int nmatch = 2;



    bool result = prog.SearchNFA(text, context, anchor, kind, match, nmatch);

    // Assuming the regex is configured to match "hello" and capture groups

    EXPECT_TRUE(result);

}



}  // namespace re2
