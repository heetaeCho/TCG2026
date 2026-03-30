#include <gtest/gtest.h>

#include "prog.h"



namespace re2 {



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_104, InitByteRangeSetsLoAndHi_104) {

    int lo = 5;

    int hi = 10;

    inst.InitByteRange(lo, hi, 0, 0);

    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

}



TEST_F(ProgInstTest_104, InitCaptureSetsCap_104) {

    int cap = 3;

    inst.InitCapture(cap, 0);

    EXPECT_EQ(inst.cap(), cap);

}



TEST_F(ProgInstTest_104, InitMatchSetsMatchId_104) {

    int match_id = 7;

    inst.InitMatch(match_id);

    EXPECT_EQ(inst.match_id(), match_id);

}



TEST_F(ProgInstTest_104, InitNopSetsOpcodeAndOut_104) {

    uint32_t out = 42;

    inst.InitNop(out);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.opcode(), kInstNop);

}



TEST_F(ProgInstTest_104, InitFailSetsOpcode_104) {

    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstFail);

}



TEST_F(ProgInstTest_104, InitAltSetsOutAndOut1_104) {

    uint32_t out = 42;

    uint32_t out1 = 84;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.out1(), out1);

}



TEST_F(ProgInstTest_104, InitEmptyWidthSetsOpcodeAndOut_104) {

    EmptyOp empty = kEmptyWordBoundary;

    uint32_t out = 99;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.empty(), empty);

}



TEST_F(ProgInstTest_104, OpcodeIsSetCorrectlyAfterInitialization_104) {

    inst.InitByteRange(5, 10, 0, 0);

    EXPECT_EQ(inst.opcode(), kInstByteRange);



    inst.InitCapture(3, 0);

    EXPECT_EQ(inst.opcode(), kInstCapture);



    inst.InitMatch(7);

    EXPECT_EQ(inst.opcode(), kInstMatch);



    inst.InitNop(42);

    EXPECT_EQ(inst.opcode(), kInstNop);



    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstFail);



    inst.InitAlt(42, 84);

    EXPECT_EQ(inst.opcode(), kInstAlt);



    inst.InitEmptyWidth(kEmptyWordBoundary, 99);

    EXPECT_EQ(inst.opcode(), kInstEmptyWidth);

}



TEST_F(ProgInstTest_104, DefaultConstructorInitializesCorrectly_104) {

    Inst default_inst;

    // Assuming default constructor initializes opcode to a known state, e.g., kInstNop

    EXPECT_EQ(default_inst.opcode(), kInstNop);

}



TEST_F(ProgInstTest_104, CopyConstructorCopiesState_104) {

    inst.InitByteRange(5, 10, 0, 0);

    Inst copy_inst(inst);

    EXPECT_EQ(copy_inst.lo(), inst.lo());

    EXPECT_EQ(copy_inst.hi(), inst.hi());

}



TEST_F(ProgInstTest_104, AssignmentOperatorCopiesState_104) {

    inst.InitByteRange(5, 10, 0, 0);

    Inst assigned_inst;

    assigned_inst = inst;

    EXPECT_EQ(assigned_inst.lo(), inst.lo());

    EXPECT_EQ(assigned_inst.hi(), inst.hi());

}



} // namespace re2
