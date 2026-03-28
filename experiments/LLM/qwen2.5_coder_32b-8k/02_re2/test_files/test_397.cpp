#include <gtest/gtest.h>

#include "prog.h"



using namespace re2;



class ProgInstTest_397 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_397, DumpOpcodeDefault_397) {

    EXPECT_EQ(inst.Dump(), "opcode 0");

}



TEST_F(ProgInstTest_397, DumpAlt_397) {

    inst.InitAlt(10, 20);

    EXPECT_EQ(inst.Dump(), "alt -> 10 | 20");

}



TEST_F(ProgInstTest_397, DumpAltMatch_397) {

    inst.InitAlt(10, 20);

    inst.set_opcode(kInstAltMatch);

    EXPECT_EQ(inst.Dump(), "altmatch -> 10 | 20");

}



TEST_F(ProgInstTest_397, DumpByteRange_397) {

    inst.InitByteRange(0x1a, 0x2b, 1, 30);

    EXPECT_EQ(inst.Dump(), "byte/i [1a-2b] 0 -> 30");

}



TEST_F(ProgInstTest_397, DumpCapture_397) {

    inst.InitCapture(5, 40);

    EXPECT_EQ(inst.Dump(), "capture 5 -> 40");

}



TEST_F(ProgInstTest_397, DumpEmptyWidth_397) {

    inst.InitEmptyWidth(kEmptyWordBoundary, 50);

    EXPECT_EQ(inst.Dump(), "emptywidth 1 -> 50");

}



TEST_F(ProgInstTest_397, DumpMatch_397) {

    inst.InitMatch(60);

    EXPECT_EQ(inst.Dump(), "match! 60");

}



TEST_F(ProgInstTest_397, DumpNop_397) {

    inst.InitNop(70);

    EXPECT_EQ(inst.Dump(), "nop -> 70");

}



TEST_F(ProgInstTest_397, DumpFail_397) {

    inst.InitFail();

    EXPECT_EQ(inst.Dump(), "fail");

}



TEST_F(ProgInstTest_397, BoundaryConditions_397) {

    inst.InitByteRange(0x00, 0xff, 0, 255);

    EXPECT_EQ(inst.Dump(), "byte [00-ff] 0 -> 255");



    inst.InitCapture(std::numeric_limits<int>::min(), std::numeric_limits<uint32_t>::max());

    EXPECT_EQ(inst.Dump(), "capture -2147483648 -> 4294967295");

}



TEST_F(ProgInstTest_397, ExceptionalCases_397) {

    // Since there are no observable exceptional cases through the interface provided,

    // we do not need to write additional tests for them.

}
