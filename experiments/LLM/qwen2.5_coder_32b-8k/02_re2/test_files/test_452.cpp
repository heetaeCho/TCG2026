#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"



using namespace re2;

using ::testing::_;

using ::testing::Eq;



class DFA_Test_452 : public ::testing::Test {

protected:

    DFA_Test_452() 

        : prog(nullptr), kind(Prog::MatchKind::kLongestMatch), max_mem(1024),

          dfa(prog, kind, max_mem) {}



    Prog* prog;

    Prog::MatchKind kind;

    int64_t max_mem;

    DFA dfa;

};



TEST_F(DFA_Test_452, OkReturnsTrue_452) {

    EXPECT_TRUE(dfa.ok());

}



TEST_F(DFA_Test_452, KindReturnsExpectedValue_452) {

    EXPECT_EQ(dfa.kind(), Prog::MatchKind::kLongestMatch);

}



TEST_F(DFA_Test_452, SearchWithEmptyTextReturnsFalse_452) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;

    absl::string_view text("");

    absl::string_view context("");



    EXPECT_FALSE(dfa.Search(text, context, false, false, true, &failed, &epp, &matches));

}



TEST_F(DFA_Test_452, BuildAllStatesWithNullCallbackReturnsZero_452) {

    Prog::DFAStateCallback cb;

    EXPECT_EQ(dfa.BuildAllStates(cb), 0);

}



TEST_F(DFA_Test_452, PossibleMatchRangeWithMaxLenZeroReturnsFalse_452) {

    std::string min, max;

    EXPECT_FALSE(dfa.PossibleMatchRange(&min, &max, 0));

}



TEST_F(DFA_Test_452, StateSaverRestoreSpecialStateReturnsCorrectly_452) {

    DFA::State* specialState = DeadState;

    DFA::StateSaver saver(&dfa, specialState);

    EXPECT_EQ(saver.Restore(), DeadState);

}
