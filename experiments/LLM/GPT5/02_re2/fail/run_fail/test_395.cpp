// File: prog_inst_initnop_test.cc

#include <gtest/gtest.h>
#include "re2/prog.h"

using namespace re2;

class ProgInstInitNopTest_395 : public ::testing::Test {
protected:
    Prog::Inst inst_;
};

// [Normal] InitNop sets opcode to kInstNop for a typical out value.
TEST_F(ProgInstInitNopTest_395, InitNopSetsOpcode_395) {
    inst_.InitNop(/*out=*/0u);
    EXPECT_EQ(inst_.opcode(), kInstNop);
}

// [Boundary] InitNop with a non-zero out value still results in kInstNop.
// We do not assert internal routing or out() because implementation is a black box.
TEST_F(ProgInstInitNopTest_395, InitNopWithNonZeroOut_395) {
    inst_.InitNop(/*out=*/123u);
    EXPECT_EQ(inst_.opcode(), kInstNop);
}

// [Boundary] InitNop with the maximum uint32 value remains observable as kInstNop.
TEST_F(ProgInstInitNopTest_395, InitNopWithMaxOut_395) {
    inst_.InitNop(/*out=*/0xFFFFFFFFu);
    EXPECT_EQ(inst_.opcode(), kInstNop);
}
