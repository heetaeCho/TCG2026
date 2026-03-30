#include <gtest/gtest.h>

#include "dfa.h"



namespace re2 {



class DFA_Test_451 : public ::testing::Test {

protected:

    DFA* dfa;



    void SetUp() override {

        dfa = new DFA();

    }



    void TearDown() override {

        delete dfa;

    }

};



TEST_F(DFA_Test_451, StateSaver_Restore_ReturnsOriginalState_451) {

    // Arrange

    State* state = reinterpret_cast<State*>(10);

    DFA::StateSaver saver(dfa, state);



    // Act

    State* restored_state = saver.Restore();



    // Assert

    EXPECT_EQ(restored_state, state);

}



TEST_F(DFA_Test_451, StateSaver_Restore_ReturnsSpecialStates_451) {

    // Arrange

    DFA::StateSaver dead_saver(dfa, DeadState);

    DFA::StateSaver match_sep_saver(dfa, reinterpret_cast<State*>(MatchSep));

    DFA::StateSaver full_match_saver(dfa, FullMatchState);

    DFA::StateSaver mark_saver(dfa, reinterpret_cast<State*>(Mark));



    // Act

    State* restored_dead_state = dead_saver.Restore();

    State* restored_match_sep_state = match_sep_saver.Restore();

    State* restored_full_match_state = full_match_saver.Restore();

    State* restored_mark_state = mark_saver.Restore();



    // Assert

    EXPECT_EQ(restored_dead_state, DeadState);

    EXPECT_EQ(restored_match_sep_state, reinterpret_cast<State*>(MatchSep));

    EXPECT_EQ(restored_full_match_state, FullMatchState);

    EXPECT_EQ(restored_mark_state, reinterpret_cast<State*>(Mark));

}



TEST_F(DFA_Test_451, StateSaver_Restore_DoesNotDeleteSpecialStates_451) {

    // Arrange

    DFA::StateSaver dead_saver(dfa, DeadState);



    // Act & Assert (Expect no delete operations)

    EXPECT_NO_THROW(dead_saver.Restore());

}



TEST_F(DFA_Test_451, StateSaver_Restore_DoesNotDeleteNonSpecialStates_451) {

    // Arrange

    State* state = new State();

    DFA::StateSaver saver(dfa, state);



    // Act & Assert (Expect no delete operations)

    EXPECT_NO_THROW(saver.Restore());

}



}  // namespace re2
