#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_InitCapture_NormalOperation_392, SetsCapAndOpcodeCorrectly_392) {

    int cap = 5;

    uint32_t out = 10;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_InitCapture_BoundaryCondition_CapZero_392, SetsCapZeroCorrectly_392) {

    int cap = 0;

    uint32_t out = 10;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_InitCapture_BoundaryCondition_OutZero_392, SetsOutZeroCorrectly_392) {

    int cap = 5;

    uint32_t out = 0;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_InitCapture_VerificationOfOpcode_392, VerifiesOpcodeIsSetCorrectly_392) {

    int cap = 5;

    uint32_t out = 10;

    inst.InitCapture(cap, out);

    EXPECT_EQ(inst.opcode(), kInstCapture);

}
