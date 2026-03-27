#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Decrypt.cc"



class Mul09TableTest : public ::testing::Test {

protected:

    Mul09Table table;

};



TEST_F(Mul09TableTest_1605, NormalOperation_1605) {

    EXPECT_EQ(table(0), 0);

    EXPECT_EQ(table(1), 9);

    EXPECT_EQ(table(2), 18);

    EXPECT_EQ(table(3), 27);

    EXPECT_EQ(table(4), 36);

    EXPECT_EQ(table(5), 45);

    EXPECT_EQ(table(6), 54);

    EXPECT_EQ(table(7), 63);

    EXPECT_EQ(table(8), 72);

    EXPECT_EQ(table(9), 81);

}



TEST_F(Mul09TableTest_1605, BoundaryConditions_1605) {

    EXPECT_EQ(table(0), 0);

    EXPECT_EQ(table(255), 81); // Assuming the implementation wraps around or clamps

}



// No exceptional or error cases are observable through the interface based on provided information.



TEST_F(Mul09TableTest_1605, ExternalInteractions_1605) {

    // Since the Mul09Table does not have any external collaborators, no tests for external interactions are needed.

}
