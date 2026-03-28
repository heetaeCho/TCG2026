#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"

#include "absl/strings/string_view.h"



using namespace re2;

using ::testing::_;

using ::testing::Eq;



class ProgTest_401 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_401, StartReturnsInitialValue_401) {

    EXPECT_EQ(prog.start(), 0);

}



TEST_F(ProgTest_401, SetStartChangesStartValue_401) {

    prog.set_start(5);

    EXPECT_EQ(prog.start(), 5);

}



TEST_F(ProgTest_401, StartUnanchoredReturnsInitialValue_401) {

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_401, SetStartUnanchoredChangesStartUnanchoredValue_401) {

    prog.set_start_unanchored(5);

    EXPECT_EQ(prog.start_unanchored(), 5);

}



TEST_F(ProgTest_401, ReversedReturnsInitialValue_401) {

    EXPECT_FALSE(prog.reversed());

}



TEST_F(ProgTest_401, SetReversedChangesReversedValue_401) {

    prog.set_reversed(true);

    EXPECT_TRUE(prog.reversed());

}



TEST_F(ProgTest_401, ListCountReturnsInitialValue_401) {

    EXPECT_EQ(prog.list_count(), 0);

}



TEST_F(ProgTest_401, InstCountReturnsInitialValue_401) {

    for (int i = 0; i < 8; ++i) {

        EXPECT_EQ(prog.inst_count(static_cast<InstOp>(i)), 0);

    }

}



TEST_F(ProgTest_401, BitStateTextMaxSizeReturnsInitialValue_401) {

    EXPECT_EQ(prog.bit_state_text_max_size(), 0);

}



TEST_F(ProgTest_401, DFA_MemReturnsInitialValue_401) {

    EXPECT_EQ(prog.dfa_mem(), 0);

}



TEST_F(ProgTest_401, SetDFA_MemChangesDFA_MemValue_401) {

    prog.set_dfa_mem(1024);

    EXPECT_EQ(prog.dfa_mem(), 1024);

}



TEST_F(ProgTest_401, AnchorStartReturnsInitialValue_401) {

    EXPECT_FALSE(prog.anchor_start());

}



TEST_F(ProgTest_401, SetAnchorStartChangesAnchorStartValue_401) {

    prog.set_anchor_start(true);

    EXPECT_TRUE(prog.anchor_start());

}



TEST_F(ProgTest_401, AnchorEndReturnsInitialValue_401) {

    EXPECT_FALSE(prog.anchor_end());

}



TEST_F(ProgTest_401, SetAnchorEndChangesAnchorEndValue_401) {

    prog.set_anchor_end(true);

    EXPECT_TRUE(prog.anchor_end());

}



TEST_F(ProgTest_401, ByteMapRangeReturnsInitialValue_401) {

    EXPECT_EQ(prog.bytemap_range(), 0);

}



TEST_F(ProgTest_401, CanPrefixAccelReturnsFalseInitially_401) {

    EXPECT_FALSE(prog.can_prefix_accel());

}



TEST_F(ProgTest_401, BytemapReturnsNonnullptrPointer_401) {

    EXPECT_NE(prog.bytemap(), nullptr);

}



TEST_F(ProgTest_401, CanBitStateReturnsFalseInitially_401) {

    EXPECT_FALSE(prog.CanBitState());

}
