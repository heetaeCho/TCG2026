#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest_106 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_106, InitByteRange_SetsCorrectValues_106) {

    int lo = 32;

    int hi = 64;

    int foldcase = 1;

    uint32_t out = 5;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_106, InitCapture_SetsCorrectValues_106) {

    int cap = 7;

    uint32_t out = 8;



    inst.InitCapture(cap, out);



    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_106, InitEmptyWidth_SetsCorrectValues_106) {

    EmptyOp empty = kEmptyBeginLine;

    uint32_t out = 9;



    inst.InitEmptyWidth(empty, out);



    EXPECT_EQ(inst.empty(), empty);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_106, InitMatch_SetsCorrectValues_106) {

    int id = 10;



    inst.InitMatch(id);



    EXPECT_EQ(inst.match_id(), id);

}



TEST_F(ProgInstTest_106, InitNop_SetsCorrectValues_106) {

    uint32_t out = 11;



    inst.InitNop(out);



    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_106, InitFail_DoesNotCrash_106) {

    inst.InitFail();

    // No assertions needed as the function should not crash

}



TEST_F(ProgInstTest_106, Opcode_ReturnsCorrectValue_AfterInitByteRange_106) {

    int lo = 32;

    int hi = 64;

    int foldcase = 1;

    uint32_t out = 5;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.opcode(), kInstByteRange);

}



TEST_F(ProgInstTest_106, FoldCase_ReturnsCorrectValue_AfterInitByteRange_106) {

    int lo = 32;

    int hi = 64;

    int foldcase = 1;

    uint32_t out = 5;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.foldcase(), foldcase);

}



TEST_F(ProgInstTest_106, FoldCase_ReturnsZero_WhenNotInitializedWithFoldCase_106) {

    int lo = 32;

    int hi = 64;

    int foldcase = 0;

    uint32_t out = 5;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.foldcase(), foldcase);

}
