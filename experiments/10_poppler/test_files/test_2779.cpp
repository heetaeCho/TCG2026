#include <gtest/gtest.h>

#include "Decrypt.cc"  // Assuming the struct definition is in this file



class Mul02TableTest_2779 : public ::testing::Test {

protected:

    Mul02Table table;

};



TEST_F(Mul02TableTest_2779, NormalOperation_2779) {

    EXPECT_EQ(table(1), 2);

    EXPECT_EQ(table(3), 6);

    EXPECT_EQ(table(5), 10);

    EXPECT_EQ(table(127), 254);

}



TEST_F(Mul02TableTest_2779, BoundaryConditions_2779) {

    EXPECT_EQ(table(0), 0);      // Minimum boundary

    EXPECT_EQ(table(255), 13);   // Maximum boundary (0xff -> 0x1b)

}



TEST_F(Mul02TableTest_2779, BitFlipCondition_2779) {

    EXPECT_EQ(table(128), 27);   // 128 is the point where the bit flip occurs

    EXPECT_EQ(table(192), 59);

}



TEST_F(Mul02TableTest_2779, FullRangeCheck_2779) {

    for (int i = 0; i < 256; ++i) {

        unsigned char expected = (i & 0x80) ? ((i << 1) ^ 0x1b) : (i << 1);

        EXPECT_EQ(table(i), expected);

    }

}
