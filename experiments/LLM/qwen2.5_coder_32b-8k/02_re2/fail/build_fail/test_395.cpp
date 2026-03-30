#include <gtest/gtest.h>

#include "prog.h"



namespace re2 {

class ProgTest_395 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgTest_395, InitNop_SetsOpcodeToNop_395) {

    inst.InitNop(1);

    EXPECT_EQ(inst.opcode(), kInstNop);

}



TEST_F(ProgTest_395, InitAlt_SetsOutAndOut1Correctly_395) {

    inst.InitAlt(2, 3);

    EXPECT_EQ(inst.out(), 2);

    EXPECT_EQ(inst.out1(), 3);

}



TEST_F(ProgTest_395, InitByteRange_SetsLoHiFoldcaseOutCorrectly_395) {

    inst.InitByteRange(4, 5, 6, 7);

    EXPECT_EQ(inst.lo(), 4);

    EXPECT_EQ(inst.hi(), 5);

    EXPECT_EQ(inst.foldcase(), 6);

    EXPECT_EQ(inst.out(), 7);

}



TEST_F(ProgTest_395, InitCapture_SetsCapAndOutCorrectly_395) {

    inst.InitCapture(8, 9);

    EXPECT_EQ(inst.cap(), 8);

    EXPECT_EQ(inst.out(), 9);

}



TEST_F(ProgTest_395, InitEmptyWidth_SetsEmptyAndOutCorrectly_395) {

    inst.InitEmptyWidth(kEmptyWordBoundary, 10);

    EXPECT_EQ(inst.empty(), kEmptyWordBoundary);

    EXPECT_EQ(inst.out(), 10);

}



TEST_F(ProgTest_395, InitMatch_SetsIdCorrectly_395) {

    inst.InitMatch(11);

    EXPECT_EQ(inst.match_id(), 11);

}



TEST_F(ProgTest_395, InitFail_SetsOpcodeToFail_395) {

    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstFail);

}



} // namespace re2
