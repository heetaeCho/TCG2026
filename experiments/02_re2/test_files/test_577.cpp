#include <gtest/gtest.h>

#include "re2/nfa.h"

#include "absl/strings/string_view.h"



using namespace re2;



class NFAFixture : public ::testing::Test {

protected:

    Prog prog;

    NFA nfa{&prog};



    void SetUp() override {

        // Setup any necessary preconditions for the tests

        prog.set_start(1); // Ensure start_ is not 0

    }

};



TEST_F(NFAFixture, Search_NormalOperation_ReturnsTrue_577) {

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_TRUE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_AnchoredStart_ReturnsTrue_577) {

    prog.set_anchor_start(true);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = true;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_TRUE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_AnchoredEnd_ReturnsTrue_577) {

    prog.set_anchor_end(true);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_TRUE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_OutsideContext_ReturnsFalse_577) {

    prog.set_anchor_start(false);

    prog.set_anchor_end(false);

    absl::string_view text = "hello";

    absl::string_view context = "world";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_InvalidNsubmatch_ReturnsFalse_577) {

    prog.set_start(1);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = -1;



    EXPECT_FALSE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_EmptyText_ReturnsFalse_577) {

    prog.set_start(1);

    absl::string_view text = "";

    absl::string_view context = "";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_NoStart_ReturnsFalse_577) {

    prog.set_start(0);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_LongestMatch_ReturnsTrue_577) {

    prog.set_start(1);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_TRUE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAFixture, Search_WithSubmatches_ReturnsTrue_577) {

    prog.set_start(1);

    absl::string_view text = "hello";

    absl::string_view context = "hello";

    bool anchored = false;

    bool longest = false;

    absl::string_view submatch[2];

    int nsubmatch = 2;



    EXPECT_TRUE(nfa.Search(text, context, anchored, longest, submatch, nsubmatch));

}
