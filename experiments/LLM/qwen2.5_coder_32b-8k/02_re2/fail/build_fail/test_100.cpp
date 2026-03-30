#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class Prog_InstTest : public ::testing::Test {

protected:

    Prog::Inst inst;

};



TEST_F(Prog_InstTest, InitAlt_SetsOutAndOut1_100) {

    uint32_t out = 42;

    uint32_t out1 = 84;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.out1(), out1);

}



TEST_F(Prog_InstTest, InitByteRange_SetsLoHiAndFoldcase_100) {

    int lo = 97;

    int hi = 122;

    int foldcase = 1;

    uint32_t out = 42;

    inst.InitByteRange(lo, hi, foldcase, out);

    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(Prog_InstTest, InitCapture_SetsCapAndOut_100) {

    int cap = 5;

    uint32_t out = 42;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(Prog_InstTest, InitEmptyWidth_SetsEmptyAndOut_100) {

    EmptyOp empty = kEmptyWordBoundary;

    uint32_t out = 42;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.empty(), empty);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(Prog_InstTest, InitMatch_SetsMatchId_100) {

    int id = 5;

    inst.InitMatch(id);

    EXPECT_EQ(inst.match_id(), id);

}



TEST_F(Prog_InstTest, InitNop_SetsOut_100) {

    uint32_t out = 42;

    inst.InitNop(out);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(Prog_InstTest, InitFail_DoesNotSetAnything_100) {

    inst.InitFail();

    // Since InitFail does not set any observable state, this test is more of a placeholder

    // to ensure the function exists and can be called without errors.

}



TEST_F(Prog_InstTest, Last_ReturnsCorrectValue_100) {

    uint32_t out = 42;

    inst.set_out_opcode(out, kInstAlt);

    EXPECT_EQ(inst.last(), (out >> 3) & 1);

}



} // namespace re2
