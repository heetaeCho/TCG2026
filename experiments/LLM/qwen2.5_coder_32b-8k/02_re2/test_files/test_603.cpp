#include <gtest/gtest.h>

#include "re2/dfa.h"

#include "re2/prog.h"



using namespace re2;



class DFA_Test_603 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

        dfa_first_match = new DFA(prog, Prog::kFirstMatch, 1024);

        dfa_longest_match = new DFA(prog, Prog::kLongestMatch, 1024);

    }



    void TearDown() override {

        delete prog;

        delete dfa_first_match;

        delete dfa_longest_match;

    }



    Prog* prog;

    DFA* dfa_first_match;

    DFA* dfa_longest_match;

};



TEST_F(DFA_Test_603, Initialization_Successful_603) {

    EXPECT_TRUE(dfa_first_match->ok());

    EXPECT_TRUE(dfa_longest_match->ok());

}



TEST_F(DFA_Test_603, Initialization_MemoryBudget_TooLow_FirstMatch_603) {

    DFA* dfa = new DFA(prog, Prog::kFirstMatch, 1);

    EXPECT_FALSE(dfa->ok());

    delete dfa;

}



TEST_F(DFA_Test_603, Initialization_MemoryBudget_TooLow_LongestMatch_603) {

    DFA* dfa = new DFA(prog, Prog::kLongestMatch, 1);

    EXPECT_FALSE(dfa->ok());

    delete dfa;

}



TEST_F(DFA_Test_603, Kind_Set_Correctly_FirstMatch_603) {

    EXPECT_EQ(dfa_first_match->kind(), Prog::kFirstMatch);

}



TEST_F(DFA_Test_603, Kind_Set_Correctly_LongestMatch_603) {

    EXPECT_EQ(dfa_longest_match->kind(), Prog::kLongestMatch);

}
