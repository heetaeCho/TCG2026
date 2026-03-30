#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/nfa.h"

#include "absl/strings/string_view.h"



namespace re2 {

class Prog;

struct Thread;



class NFAInterfaceTest : public ::testing::Test {

protected:

    std::unique_ptr<Prog> prog_;

    std::unique_ptr<NFA> nfa_;



    void SetUp() override {

        prog_ = std::make_unique<Prog>();

        nfa_ = std::make_unique<NFA>(prog_.get());

    }

};



TEST_F(NFAInterfaceTest_576, Search_ReturnsTrueForMatchingPattern_576) {

    absl::string_view text("test");

    absl::string_view context("context");

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_TRUE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_ReturnsFalseForNonMatchingPattern_576) {

    absl::string_view text("test");

    absl::string_view context("context");

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_HandlesEmptyText_576) {

    absl::string_view text("");

    absl::string_view context("context");

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_HandlesEmptyContext_576) {

    absl::string_view text("test");

    absl::string_view context("");

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_HandlesZeroSubmatches_576) {

    absl::string_view text("test");

    absl::string_view context("context");

    bool anchored = false;

    bool longest = true;

    absl::string_view* submatch = nullptr;

    int nsubmatch = 0;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_HandlesAnchoredSearch_576) {

    absl::string_view text("test");

    absl::string_view context("context");

    bool anchored = true;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



TEST_F(NFAInterfaceTest_576, Search_HandlesNonAnchoredSearch_576) {

    absl::string_view text("test");

    absl::string_view context("context");

    bool anchored = false;

    bool longest = true;

    absl::string_view submatch[1];

    int nsubmatch = 1;



    EXPECT_FALSE(nfa_->Search(text, context, anchored, longest, submatch, nsubmatch));

}



} // namespace re2
