#include <gtest/gtest.h>

#include "TestProjects/re2/re2/prog.h"



using namespace re2;



class ProgInstTest_108 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_108, InitMatchSetsCorrectOpcodeAndId_108) {

    int match_id = 42;

    inst.InitMatch(match_id);

    EXPECT_EQ(inst.opcode(), kInstMatch);

    EXPECT_EQ(inst.match_id(), match_id);

}



TEST_F(ProgInstTest_108, MatchIdThrowsOnIncorrectOpcode_108) {

    inst.set_opcode(kInstAlt);

    EXPECT_DEATH(inst.match_id(), "opcode\\(\\) == kInstMatch");

}



TEST_F(ProgInstTest_108, InitByteRangeSetsCorrectValues_108) {

    int lo = 97;

    int hi = 122;

    int foldcase = 1;

    uint32_t out = 5;

    inst.InitByteRange(lo, hi, foldcase, out);

    EXPECT_EQ(inst.opcode(), kInstByteRange);

    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_108, InitCaptureSetsCorrectValues_108) {

    int cap = 3;

    uint32_t out = 6;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.opcode(), kInstCapture);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_108, InitAltSetsCorrectValues_108) {

    uint32_t out = 7;

    uint32_t out1 = 8;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.opcode(), kInstAlt);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

    EXPECT_EQ(inst.out1_, static_cast<int>(out1));

}



TEST_F(ProgInstTest_108, InitNopSetsCorrectOpcodeAndOut_108) {

    uint32_t out = 9;

    inst.InitNop(out);

    EXPECT_EQ(inst.opcode(), kInstNop);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_108, InitFailSetsCorrectOpcode_108) {

    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstFail);

}
