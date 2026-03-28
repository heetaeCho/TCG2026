#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest_396 : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_396, InitFailSetsOpcodeToFail_396) {

    inst.InitFail();

    EXPECT_EQ(inst.opcode(), kInstFail);

}



TEST_F(ProgInstTest_396, DumpReturnsNonEmptyString_396) {

    std::string dump = inst.Dump();

    EXPECT_FALSE(dump.empty());

}



// Boundary Conditions

TEST_F(ProgInstTest_396, InitByteRangeWithMinValues_396) {

    inst.InitByteRange(0, 0, 0, 0);

    EXPECT_EQ(inst.lo(), 0);

    EXPECT_EQ(inst.hi(), 0);

    EXPECT_EQ(inst.foldcase(), 0);

}



TEST_F(ProgInstTest_396, InitByteRangeWithMaxValues_396) {

    inst.InitByteRange(255, 255, 1, UINT32_MAX);

    EXPECT_EQ(inst.lo(), 255);

    EXPECT_EQ(inst.hi(), 255);

    EXPECT_EQ(inst.foldcase(), 1);

}



// Exceptional or Error Cases

// Since the methods do not throw exceptions based on the provided interface,

// we can only test for logical consistency.



TEST_F(ProgInstTest_396, InitCaptureWithNegativeCap_396) {

    inst.InitCapture(-1, 0);

    EXPECT_EQ(inst.cap(), -1);

}



TEST_F(ProgInstTest_396, InitEmptyWidthWithInvalidOpcode_396) {

    EmptyOp invalid_empty = static_cast<EmptyOp>(-1);

    inst.InitEmptyWidth(invalid_empty, 0);

    // Assuming Dump() will reflect the incorrect state

    std::string dump = inst.Dump();

    EXPECT_FALSE(dump.empty());

}



TEST_F(ProgInstTest_396, InitMatchWithNegativeID_396) {

    inst.InitMatch(-1);

    EXPECT_EQ(inst.match_id(), -1);

}
