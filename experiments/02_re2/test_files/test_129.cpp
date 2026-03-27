#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_129 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_129, Bytemap_ReturnsNonZeroPointer_129) {

    EXPECT_NE(prog->bytemap(), nullptr);

}



TEST_F(ProgTest_129, Start_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->start(), 0);

}



TEST_F(ProgTest_129, StartUnanchored_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->start_unanchored(), 0);

}



TEST_F(ProgTest_129, Reversed_DefaultValueIsFalse_129) {

    EXPECT_FALSE(prog->reversed());

}



TEST_F(ProgTest_129, ListCount_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->list_count(), 0);

}



TEST_F(ProgTest_129, InstCount_Op_ReturnsNonNegative_129) {

    for (int i = 0; i < 8; ++i) {

        EXPECT_GE(prog->inst_count(static_cast<InstOp>(i)), 0);

    }

}



TEST_F(ProgTest_129, ListHeads_ReturnsNonNullPointer_129) {

    EXPECT_NE(prog->list_heads(), nullptr);

}



TEST_F(ProgTest_129, BitStateTextMaxSize_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->bit_state_text_max_size(), 0);

}



TEST_F(ProgTest_129, DFA_Mem_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->dfa_mem(), 0);

}



TEST_F(ProgTest_129, AnchorStart_DefaultValueIsFalse_129) {

    EXPECT_FALSE(prog->anchor_start());

}



TEST_F(ProgTest_129, AnchorEnd_DefaultValueIsFalse_129) {

    EXPECT_FALSE(prog->anchor_end());

}



TEST_F(ProgTest_129, ByteMapRange_DefaultValueIsZero_129) {

    EXPECT_EQ(prog->bytemap_range(), 0);

}



// Additional tests for boundary conditions and exceptional cases can be added here

// if the interface allows for such scenarios to be observed.



TEST_F(ProgTest_129, SetStartAndGetStart_ConsistencyCheck_129) {

    int new_start = 5;

    prog->set_start(new_start);

    EXPECT_EQ(prog->start(), new_start);

}



TEST_F(ProgTest_129, SetStartUnanchoredAndGetStartUnanchored_ConsistencyCheck_129) {

    int new_start_unanchored = 10;

    prog->set_start_unanchored(new_start_unanchored);

    EXPECT_EQ(prog->start_unanchored(), new_start_unanchored);

}



TEST_F(ProgTest_129, SetReversedAndGetReversed_ConsistencyCheck_129) {

    bool new_reversed = true;

    prog->set_reversed(new_reversed);

    EXPECT_TRUE(prog->reversed());

}



TEST_F(ProgTest_129, SetDFA_MemAndGetDFA_Mem_ConsistencyCheck_129) {

    int64_t new_dfa_mem = 1024;

    prog->set_dfa_mem(new_dfa_mem);

    EXPECT_EQ(prog->dfa_mem(), new_dfa_mem);

}



TEST_F(ProgTest_129, SetAnchorStartAndGetAnchorStart_ConsistencyCheck_129) {

    bool new_anchor_start = true;

    prog->set_anchor_start(new_anchor_start);

    EXPECT_TRUE(prog->anchor_start());

}



TEST_F(ProgTest_129, SetAnchorEndAndGetAnchorEnd_ConsistencyCheck_129) {

    bool new_anchor_end = true;

    prog->set_anchor_end(new_anchor_end);

    EXPECT_TRUE(prog->anchor_end());

}
