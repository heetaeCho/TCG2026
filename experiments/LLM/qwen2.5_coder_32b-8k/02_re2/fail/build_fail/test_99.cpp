#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "prog.h"



namespace re2 {



class Prog_99Test : public ::testing::Test {

protected:

    Prog prog;

    Prog::Inst inst;



    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(Prog_99Test, OpcodeReturnsExpectedValue_99) {

    inst.set_opcode(kAlt);

    EXPECT_EQ(inst.opcode(), kAlt);

}



TEST_F(Prog_99Test, OutReturnsExpectedValue_99) {

    int expected_out = 42;

    inst.set_out(expected_out);

    EXPECT_EQ(inst.out(), expected_out);

}



TEST_F(Prog_99Test, InitAltSetsCorrectValues_99) {

    uint32_t out = 10;

    uint32_t out1 = 20;

    inst.InitAlt(out, out1);

    EXPECT_EQ(inst.opcode(), kAlt);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

    EXPECT_EQ(inst.out1(), static_cast<int>(out1));

}



TEST_F(Prog_99Test, InitByteRangeSetsCorrectValues_99) {

    int lo = 1;

    int hi = 2;

    int foldcase = 3;

    uint32_t out = 4;

    inst.InitByteRange(lo, hi, foldcase, out);

    EXPECT_EQ(inst.opcode(), kByteRange);

    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(Prog_99Test, InitCaptureSetsCorrectValues_99) {

    int cap = 5;

    uint32_t out = 6;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.opcode(), kCapture);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(Prog_99Test, InitEmptyWidthSetsCorrectValues_99) {

    EmptyOp empty = kNoWidth;

    uint32_t out = 7;

    inst.InitEmptyWidth(empty, out);

    EXPECT_EQ(inst.opcode(), kEmptyWidth);

    EXPECT_EQ(inst.empty(), empty);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(Prog_99Test, InitMatchSetsCorrectValues_99) {

    int id = 8;

    inst.InitMatch(id);

    EXPECT_EQ(inst.opcode(), kInstruction::kMatch);

    EXPECT_EQ(inst.match_id(), id);

}



TEST_F(Prog_99Test, InitNopSetsCorrectValues_99) {

    uint32_t out = 9;

    inst.InitNop(out);

    EXPECT_EQ(inst.opcode(), kNop);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(Prog_99Test, InitFailSetsCorrectOpcode_99) {

    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstruction::kFail);

}



TEST_F(Prog_99Test, DumpIsNonEmptyString_99) {

    std::string dump = inst.Dump();

    EXPECT_FALSE(dump.empty());

}



}  // namespace re2
