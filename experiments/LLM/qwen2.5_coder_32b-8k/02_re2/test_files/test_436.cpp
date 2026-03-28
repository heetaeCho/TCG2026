#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the DFA and State class definitions are in re2/dfa.h

#include "re2/dfa.h"



using namespace re2;



class DFATest_436 : public ::testing::Test {

protected:

    DFA dfa;

};



TEST_F(DFATest_436, IsMatch_ReturnsTrueForFullMatchState_436) {

    State state = {nullptr, 0, {}};

    state.flag_ = FullMatchState;

    EXPECT_TRUE(state.IsMatch());

}



TEST_F(DFATest_436, IsMatch_ReturnsFalseForNonMatchState_436) {

    State state = {nullptr, 0, {}};

    state.flag_ = DeadState;

    EXPECT_FALSE(state.IsMatch());

}



TEST_F(DFATest_436, IsMatch_ReturnsFalseForMarkState_436) {

    State state = {nullptr, 0, {}};

    state.flag_ = Mark;

    EXPECT_FALSE(state.IsMatch());

}



TEST_F(DFATest_436, IsMatch_ReturnsFalseForMatchSep_436) {

    State state = {nullptr, MatchSep, {}};

    EXPECT_FALSE(state.IsMatch());

}
