#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_InitAlt_NormalOperation_390, SetsOutOpcodeAndOut1Correctly_390) {

    uint32_t out = 42;

    uint32_t out1 = 84;



    inst.InitAlt(out, out1);



    EXPECT_EQ(inst.out(), static_cast<int>(out));

    EXPECT_EQ(inst.opcode(), kInstAlt);

    EXPECT_EQ(inst.out1_, static_cast<uint32_t>(out1));

}



TEST_F(ProgInstTest_InitAlt_BoundaryConditions_390, HandlesZeroValues_390) {

    uint32_t out = 0;

    uint32_t out1 = 0;



    inst.InitAlt(out, out1);



    EXPECT_EQ(inst.out(), static_cast<int>(out));

    EXPECT_EQ(inst.opcode(), kInstAlt);

    EXPECT_EQ(inst.out1_, static_cast<uint32_t>(out1));

}



TEST_F(ProgInstTest_InitAlt_BoundaryConditions_390, HandlesMaxValues_390) {

    uint32_t out = UINT32_MAX;

    uint32_t out1 = UINT32_MAX;



    inst.InitAlt(out, out1);



    EXPECT_EQ(inst.out(), static_cast<int>(out));

    EXPECT_EQ(inst.opcode(), kInstAlt);

    EXPECT_EQ(inst.out1_, static_cast<uint32_t>(out1));

}



}  // namespace re2
