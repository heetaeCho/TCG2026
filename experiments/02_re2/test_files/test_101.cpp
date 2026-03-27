#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest_101 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_101, InitAlt_SetsOutAndOut1Correctly_101) {

    uint32_t out = 5;

    uint32_t out1 = 10;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.out(), out);

    EXPECT_EQ(inst.out1(), out1);

}



TEST_F(ProgInstTest_101, InitByteRange_SetsLoHiAndFoldcaseCorrectly_101) {

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



TEST_F(ProgInstTest_101, InitCapture_SetsCapAndOutCorrectly_101) {

    int cap = 2;

    uint32_t out = 8;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_101, InitEmptyWidth_SetsEmptyAndOutCorrectly_101) {

    EmptyOp empty = kEmptyWordBoundary;

    uint32_t out = 9;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.empty(), empty);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_101, InitMatch_SetsIdCorrectly_101) {

    int id = 4;

    inst.InitMatch(id);

    EXPECT_EQ(inst.match_id(), id);

}



TEST_F(ProgInstTest_101, InitNop_SetsOutCorrectly_101) {

    uint32_t out = 6;

    inst.InitNop(out);

    EXPECT_EQ(inst.out(), out);

}



TEST_F(ProgInstTest_101, InitFail_OutIsZero_101) {

    inst.InitFail();

    EXPECT_EQ(inst.out(), 0);

}



TEST_F(ProgInstTest_101, Dump_ReturnsNonEmptyString_101) {

    std::string dump = inst.Dump();

    EXPECT_FALSE(dump.empty());

}
