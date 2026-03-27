#include <gtest/gtest.h>

#include "prog.h"



using namespace re2;



class ProgInstTest_393 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_393, InitEmptyWidth_SetsOpcodeAndOut_393) {

    uint32_t out = 42;

    EmptyOp empty = kEmptyWordBoundary;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.opcode(), kInstEmptyWidth);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_393, InitEmptyWidth_SetsEmptyOp_393) {

    uint32_t out = 42;

    EmptyOp empty = kEmptyLineBoundary;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.empty(), empty);

}



TEST_F(ProgInstTest_393, InitEmptyWidth_ZeroOut_Valid_393) {

    uint32_t out = 0;

    EmptyOp empty = kEmptyWordBoundary;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.opcode(), kInstEmptyWidth);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_393, InitEmptyWidth_MaxOut_Valid_393) {

    uint32_t out = std::numeric_limits<uint32_t>::max();

    EmptyOp empty = kEmptyWordBoundary;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.opcode(), kInstEmptyWidth);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_393, InitEmptyWidth_OutAlreadySet_AssertionFailure_393) {

    uint32_t out = 42;

    EmptyOp empty = kEmptyWordBoundary;

    inst.set_out_opcode(out, kInstByteRange); // Setting out_opcode_ to something other than 0

    EXPECT_DEATH(inst.InitEmptyWidth(empty, out), ".*out_opcode_.*");

}
