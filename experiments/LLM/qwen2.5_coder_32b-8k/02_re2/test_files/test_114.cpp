#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_114 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_114, StartUnanchored_DefaultValue_114) {

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_114, SetStartUnanchored_NormalOperation_114) {

    int new_start_unanchored = 5;

    prog.set_start_unanchored(new_start_unanchored);

    EXPECT_EQ(prog.start_unanchored(), new_start_unanchored);

}



TEST_F(ProgTest_114, BoundaryCondition_StartUnanchored_114) {

    int max_int = std::numeric_limits<int>::max();

    prog.set_start_unanchored(max_int);

    EXPECT_EQ(prog.start_unanchored(), max_int);



    int min_int = std::numeric_limits<int>::min();

    prog.set_start_unanchored(min_int);

    EXPECT_EQ(prog.start_unanchored(), min_int);

}



TEST_F(ProgTest_114, Start_DefaultValue_114) {

    EXPECT_EQ(prog.start(), 0);

}



TEST_F(ProgTest_114, SetStart_NormalOperation_114) {

    int new_start = 5;

    prog.set_start(new_start);

    EXPECT_EQ(prog.start(), new_start);

}



TEST_F(ProgTest_114, BoundaryCondition_Start_114) {

    int max_int = std::numeric_limits<int>::max();

    prog.set_start(max_int);

    EXPECT_EQ(prog.start(), max_int);



    int min_int = std::numeric_limits<int>::min();

    prog.set_start(min_int);

    EXPECT_EQ(prog.start(), min_int);

}



TEST_F(ProgTest_114, Reversed_DefaultValue_114) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_114, SetReversed_NormalOperation_114) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());



    prog.set_reversed(false);

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_114, AnchorStart_DefaultValue_114) {

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_114, SetAnchorStart_NormalOperation_114) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());



    prog.set_anchor_start(false);

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_114, AnchorEnd_DefaultValue_114) {

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_114, SetAnchorEnd_NormalOperation_114) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());



    prog.set_anchor_end(false);

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_114, ListCount_DefaultValue_114) {

    EXPECT_EQ(prog.list_count(), 0);

}



// Assuming list_count is set internally and we can't change it directly via public interface

// So no SetListCount test case



TEST_F(ProgTest_114, InstCount_DefaultValue_114) {

    for (int i = 0; i < 8; ++i) {

        EXPECT_EQ(prog.inst_count(static_cast<InstOp>(i)), 0);

    }

}



// Assuming inst_count is set internally and we can't change it directly via public interface

// So no SetInstCount test case



TEST_F(ProgTest_114, BitStateTextMaxSize_DefaultValue_114) {

    EXPECT_EQ(prog.bit_state_text_max_size(), 0);

}



TEST_F(ProgTest_114, DFA_Mem_DefaultValue_114) {

    EXPECT_EQ(prog.dfa_mem(), 0);

}



TEST_F(ProgTest_114, SetDFA_Mem_NormalOperation_114) {

    int64_t new_dfa_mem = 500;

    prog.set_dfa_mem(new_dfa_mem);

    EXPECT_EQ(prog.dfa_mem(), new_dfa_mem);



    int64_t max_int64 = std::numeric_limits<int64_t>::max();

    prog.set_dfa_mem(max_int64);

    EXPECT_EQ(prog.dfa_mem(), max_int64);



    int64_t min_int64 = std::numeric_limits<int64_t>::min();

    prog.set_dfa_mem(min_int64);

    EXPECT_EQ(prog.dfa_mem(), min_int64);

}



TEST_F(ProgTest_114, CanPrefixAccel_DefaultValue_114) {

    EXPECT_FALSE(prog.can_prefix_accel());

}
