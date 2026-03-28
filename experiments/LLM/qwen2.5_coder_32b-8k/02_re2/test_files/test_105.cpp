#include <gtest/gtest.h>

#include "prog.h"



using namespace re2;



class ProgInstTest_105 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_105, InitByteRangeSetsValuesCorrectly_105) {

    int lo = 10;

    int hi = 20;

    int foldcase = 1;

    uint32_t out = 30;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_105, OpcodeIsSetToByteRangeAfterInitByteRange_105) {

    int lo = 10;

    int hi = 20;

    int foldcase = 1;

    uint32_t out = 30;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.opcode(), kInstByteRange);

}



TEST_F(ProgInstTest_105, HiReturnsCorrectValueAfterInitByteRange_105) {

    int lo = 10;

    int hi = 20;

    int foldcase = 1;

    uint32_t out = 30;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.hi(), hi);

}



TEST_F(ProgInstTest_105, HiThrowsAssertionIfOpcodeIsNotByteRange_105) {

    // Since we cannot directly test assertions without causing the test to fail,

    // we assume that if the opcode is not kInstByteRange, calling hi() will result

    // in an assertion failure. This test case is more of a documentation of expected behavior.

    EXPECT_DEATH(inst.hi(), "opcode\\(.*\\) == kInstByteRange");

}



TEST_F(ProgInstTest_105, InitCaptureSetsValuesCorrectly_105) {

    int cap = 5;

    uint32_t out = 15;



    inst.InitCapture(cap, out);



    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_105, OpcodeIsSetToCaptureAfterInitCapture_105) {

    int cap = 5;

    uint32_t out = 15;



    inst.InitCapture(cap, out);



    EXPECT_EQ(inst.opcode(), kInstCapture);

}
