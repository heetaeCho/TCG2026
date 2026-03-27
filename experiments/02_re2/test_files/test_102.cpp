#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest_102 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_102, Out1_ReturnsCorrectValueForAlt_102) {

    uint32_t expected_out1 = 42;

    inst.InitAlt(10, expected_out1);

    EXPECT_EQ(inst.out1(), expected_out1);

}



TEST_F(ProgInstTest_102, Out1_ReturnsCorrectValueForAltMatch_102) {

    uint32_t expected_out1 = 42;

    inst.set_opcode(kInstAltMatch);

    inst.out1_ = expected_out1;

    EXPECT_EQ(inst.out1(), expected_out1);

}



TEST_F(ProgInstTest_102, Out1_ReturnsZeroForNonAltInstructions_102) {

    inst.InitByteRange(10, 20, 0, 30);

    EXPECT_EQ(inst.out1(), 0);

}



TEST_F(ProgInstTest_102, Cap_ReturnsCorrectValueAfterInitCapture_102) {

    int expected_cap = 5;

    inst.InitCapture(expected_cap, 10);

    EXPECT_EQ(inst.cap(), expected_cap);

}



TEST_F(ProgInstTest_102, MatchId_ReturnsCorrectValueAfterInitMatch_102) {

    int expected_id = 7;

    inst.InitMatch(expected_id);

    EXPECT_EQ(inst.match_id(), expected_id);

}
