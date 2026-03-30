#include <gtest/gtest.h>

#include "Decrypt.cc"  // Adjust the include path as necessary



namespace {



class InvMixColumnsWTest : public ::testing::Test {

protected:

    unsigned int w[4];



    void SetUp() override {

        // Initialize with known values for consistency across tests

        w[0] = 0x12345678;

        w[1] = 0x9abcdef0;

        w[2] = 0x11223344;

        w[3] = 0x55667788;

    }

};



TEST_F(InvMixColumnsWTest_NormalOperation_1611, TestNormalInput_1611) {

    invMixColumnsW(w);

    // Expected values are derived from the known behavior of the function

    EXPECT_NE(w[0], 0x12345678);  // Ensure some transformation occurred

    EXPECT_NE(w[1], 0x9abcdef0);

    EXPECT_NE(w[2], 0x11223344);

    EXPECT_NE(w[3], 0x55667788);

}



TEST_F(InvMixColumnsWTest_BoundaryConditions_1611, TestZeroInput_1611) {

    w[0] = 0x00000000;

    w[1] = 0x00000000;

    w[2] = 0x00000000;

    w[3] = 0x00000000;

    invMixColumnsW(w);

    EXPECT_EQ(w[0], 0x00000000);  // Zero should map to zero

    EXPECT_EQ(w[1], 0x00000000);

    EXPECT_EQ(w[2], 0x00000000);

    EXPECT_EQ(w[3], 0x00000000);

}



TEST_F(InvMixColumnsWTest_BoundaryConditions_1611, TestMaxInput_1611) {

    w[0] = 0xFFFFFFFF;

    w[1] = 0xFFFFFFFF;

    w[2] = 0xFFFFFFFF;

    w[3] = 0xFFFFFFFF;

    invMixColumnsW(w);

    // Expected values are derived from the known behavior of the function

    EXPECT_NE(w[0], 0xFFFFFFFF);  // Ensure some transformation occurred

    EXPECT_NE(w[1], 0xFFFFFFFF);

    EXPECT_NE(w[2], 0xFFFFFFFF);

    EXPECT_NE(w[3], 0xFFFFFFFF);

}



}  // namespace
