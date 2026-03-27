#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_124, AnchorStart_DefaultValue_124) {

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_124, SetAnchorStart_ChangesValue_124) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());



    prog.set_anchor_start(false);

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_124, AnchorEnd_DefaultValue_124) {

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_124, SetAnchorEnd_ChangesValue_124) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());



    prog.set_anchor_end(false);

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_124, Reversed_DefaultValue_124) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_124, SetReversed_ChangesValue_124) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());



    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_124, Start_DefaultValue_124) {

    EXPECT_EQ(prog.start(), 0);

}



TEST_F(ProgTest_124, SetStart_ChangesValue_124) {

    prog.set_start(10);

    EXPECT_EQ(prog.start(), 10);



    prog.set_start(0);

    EXPECT_EQ(prog.start(), 0);

}



TEST_F(ProgTest_124, StartUnanchored_DefaultValue_124) {

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_124, SetStartUnanchored_ChangesValue_124) {

    prog.set_start_unanchored(15);

    EXPECT_EQ(prog.start_unanchored(), 15);



    prog.set_start_unanchored(0);

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_124, DFA_Memory_DefaultValue_124) {

    EXPECT_EQ(prog.dfa_mem(), 0);

}



TEST_F(ProgTest_124, SetDFAMemory_ChangesValue_124) {

    prog.set_dfa_mem(1024);

    EXPECT_EQ(prog.dfa_mem(), 1024);



    prog.set_dfa_mem(0);

    EXPECT_EQ(prog.dfa_mem(), 0);

}



TEST_F(ProgTest_124, ListCount_DefaultValue_124) {

    EXPECT_EQ(prog.list_count(), 0);

}
