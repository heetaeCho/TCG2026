#include <gtest/gtest.h>

#include "re2/prog.h"

#include "absl/strings/string_view.h"



using namespace re2;



class ProgTest : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_454, SearchDFA_NormalOperation_KFirstMatch_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kFirstMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_NormalOperation_KLongestMatch_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kLongestMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_NormalOperation_KFullMatch_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kFullMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_NormalOperation_KManyMatch_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kManyMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_BoundaryCondition_EmptyText_454) {

    absl::string_view text = "";

    bool failed = false;

    SparseSet matches;

    ASSERT_FALSE(prog.SearchDFA(text, text, kAnchored, kFirstMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_BoundaryCondition_NullContext_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, "", kAnchored, kFirstMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_ErrorCase_FailedFlagSet_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    // Assuming some condition sets the failed flag in the implementation

    ASSERT_FALSE(prog.SearchDFA(text, text, kAnchored, kFirstMatch, nullptr, &failed, &matches));

    ASSERT_TRUE(failed);

}



TEST_F(ProgTest_454, SearchDFA_Verification_AnchorStart_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    prog.set_anchor_start(true);

    ASSERT_FALSE(prog.SearchDFA(text.substr(1), text, kAnchored, kFirstMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_Verification_AnchorEnd_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    prog.set_anchor_end(true);

    ASSERT_FALSE(prog.SearchDFA(text.substr(0, 4), text, kAnchored, kFirstMatch, nullptr, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_Verification_Match0NotNull_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    absl::string_view match0;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kFirstMatch, &match0, &failed, &matches));

}



TEST_F(ProgTest_454, SearchDFA_Verification_MatchesNotNull_454) {

    absl::string_view text = "hello";

    bool failed = false;

    SparseSet matches;

    ASSERT_TRUE(prog.SearchDFA(text, text, kAnchored, kManyMatch, nullptr, &failed, &matches));

}
