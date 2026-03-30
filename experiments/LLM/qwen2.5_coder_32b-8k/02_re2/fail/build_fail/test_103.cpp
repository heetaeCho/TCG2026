#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_103, InitCaptureSetsCapAndOpcode_103) {

    inst.InitCapture(5, 10);

    EXPECT_EQ(inst.cap(), 5);

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstCapture);

}



TEST_F(ProgInstTest_103, CapThrowsWhenOpcodeIsNotCapture_103) {

    inst.InitByteRange(0, 255, 0, 10);

    EXPECT_DEATH(inst.cap(), ".*opcode\\(.* == kInstCapture");

}



TEST_F(ProgInstTest_103, InitAltSetsOutAndOut1_103) {

    inst.InitAlt(10, 20);

    EXPECT_EQ(inst.out(), 10);

    EXPECT_EQ(inst.out1(), 20);

}



TEST_F(ProgInstTest_103, InitByteRangeSetsLoHiFoldcaseAndOpcode_103) {

    inst.InitByteRange(10, 20, 1, 30);

    EXPECT_EQ(inst.lo(), 10);

    EXPECT_EQ(inst.hi(), 20);

    EXPECT_EQ(inst.foldcase(), 1);

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstByteRange);

}



TEST_F(ProgInstTest_103, InitEmptyWidthSetsEmptyAndOpcode_103) {

    inst.InitEmptyWidth(kEmptyWordBoundary, 40);

    EXPECT_EQ(inst.empty(), kEmptyWordBoundary);

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstEmptyWidth);

}



TEST_F(ProgInstTest_103, InitMatchSetsMatchIdAndOpcode_103) {

    inst.InitMatch(50);

    EXPECT_EQ(inst.match_id(), 50);

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstMatch);

}



TEST_F(ProgInstTest_103, InitNopSetsOutAndOpcode_103) {

    inst.InitNop(60);

    EXPECT_EQ(inst.out(), 60);

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstNop);

}



TEST_F(ProgInstTest_103, InitFailSetsOpcodeToFail_103) {

    inst.InitFail();

    EXPECT_EQ(static_cast<int>(inst.opcode()), kInstFail);

}
