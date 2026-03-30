#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_126 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_126, AnchorEnd_DefaultValue_False_126) {

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_126, SetAnchorEnd_ChangeToTrue_ReturnsTrue_126) {

    prog->set_anchor_end(true);

    EXPECT_TRUE(prog->anchor_end());

}



TEST_F(ProgTest_126, SetAnchorEnd_ChangeToFalse_ReturnsFalse_126) {

    prog->set_anchor_end(false);

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_126, AnchorStart_DefaultValue_False_126) {

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_126, SetAnchorStart_ChangeToTrue_ReturnsTrue_126) {

    prog->set_anchor_start(true);

    EXPECT_TRUE(prog->anchor_start());

}



TEST_F(ProgTest_126, SetAnchorStart_ChangeToFalse_ReturnsFalse_126) {

    prog->set_anchor_start(false);

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_126, Reversed_DefaultValue_False_126) {

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_126, SetReversed_ChangeToTrue_ReturnsTrue_126) {

    prog->set_reversed(true);

    EXPECT_TRUE(prog->reversed());

}



TEST_F(ProgTest_126, SetReversed_ChangeToFalse_ReturnsFalse_126) {

    prog->set_reversed(false);

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_126, Start_DefaultValue_Zero_126) {

    EXPECT_EQ(prog->start(), 0);

}



TEST_F(ProgTest_126, SetStart_ChangeToPositive_ReturnsSame_126) {

    prog->set_start(42);

    EXPECT_EQ(prog->start(), 42);

}



TEST_F(ProgTest_126, StartUnanchored_DefaultValue_Zero_126) {

    EXPECT_EQ(prog->start_unanchored(), 0);

}



TEST_F(ProgTest_126, SetStartUnanchored_ChangeToPositive_ReturnsSame_126) {

    prog->set_start_unanchored(42);

    EXPECT_EQ(prog->start_unanchored(), 42);

}



TEST_F(ProgTest_126, DfaMem_DefaultValue_Zero_126) {

    EXPECT_EQ(prog->dfa_mem(), 0);

}



TEST_F(ProgTest_126, SetDfaMem_ChangeToPositive_ReturnsSame_126) {

    prog->set_dfa_mem(12345);

    EXPECT_EQ(prog->dfa_mem(), 12345);

}
