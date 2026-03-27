#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest_109 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_109, InitAltSetsOutAndOut1_109) {

    uint32_t out = 5;

    uint32_t out1 = 6;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.out1(), out1);

}



TEST_F(ProgInstTest_109, InitByteRangeSetsLoHiFoldcaseAndOut_109) {

    int lo = 32;

    int hi = 64;

    int foldcase = 1;

    uint32_t out = 7;

    inst.InitByteRange(lo, hi, foldcase, out);

    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_109, InitCaptureSetsCapAndOut_109) {

    int cap = 2;

    uint32_t out = 8;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_109, InitEmptyWidthSetsEmptyAndOut_109) {

    EmptyOp empty = kEmptyWordBoundary;

    uint32_t out = 9;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.empty(), empty);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_109, InitMatchSetsMatchId_109) {

    int match_id = 42;

    inst.InitMatch(match_id);

    EXPECT_EQ(inst.match_id(), match_id);

}



TEST_F(ProgInstTest_109, InitNopSetsOut_109) {

    uint32_t out = 10;

    inst.InitNop(out);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_109, InitFailDoesNotThrowException_109) {

    EXPECT_NO_THROW(inst.InitFail());

}



TEST_F(ProgInstTest_109, DefaultConstructorInitializesOpcodeToZero_109) {

    EXPECT_EQ(inst.opcode(), kInstAlt); // Assuming default opcode is 0 (kInstAlt)

}
