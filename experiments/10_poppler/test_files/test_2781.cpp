#include <gtest/gtest.h>

#include "Decrypt.cc"  // Assuming the Mul09Table struct is defined in this file



class Mul09TableTest_2781 : public ::testing::Test {

protected:

    Mul09Table table;

};



TEST_F(Mul09TableTest_2781, NormalOperation_ZeroInput_2781) {

    EXPECT_EQ(table(0), 0);

}



TEST_F(Mul09TableTest_2781, NormalOperation_MaxValueInput_2781) {

    EXPECT_EQ(table(255), table.operator()(255));

}



TEST_F(Mul09TableTest_2781, BoundaryCondition_OneInput_2781) {

    EXPECT_EQ(table(1), 9);

}



TEST_F(Mul09TableTest_2781, BoundaryCondition_HalfwayPointInput_2781) {

    EXPECT_EQ(table(128), table.operator()(128));

}



TEST_F(Mul09TableTest_2781, ExceptionalCase_OutOfBoundsNegative_2781) {

    // Since the operator() takes uint8_t, negative values are not possible

    // This test is more of a conceptual check as unsigned char cannot be negative

    EXPECT_EQ(table(static_cast<uint8_t>(-1)), table(255));

}



TEST_F(Mul09TableTest_2781, ExceptionalCase_OutOfBoundsPositive_2781) {

    // Since the operator() takes uint8_t, values greater than 255 are truncated

    EXPECT_EQ(table(static_cast<uint8_t>(256)), table(0));

}

```


