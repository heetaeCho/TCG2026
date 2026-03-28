#include <gtest/gtest.h>



// Mocking external collaborators is not needed for this inline function as it does not interact with any external entities.



// Test suite for sha256Maj function

class Sha256MajTest_1629 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary

};



TEST_F(Sha256MajTest_1629, NormalOperation_1629) {

    unsigned int x = 0b11110000;

    unsigned int y = 0b10101010;

    unsigned int z = 0b00001111;



    unsigned int result = sha256Maj(x, y, z);

    unsigned int expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha256MajTest_1629, BoundaryConditions_AllZeros_1629) {

    unsigned int x = 0;

    unsigned int y = 0;

    unsigned int z = 0;



    unsigned int result = sha256Maj(x, y, z);

    EXPECT_EQ(result, 0);

}



TEST_F(Sha256MajTest_1629, BoundaryConditions_AllOnes_1629) {

    unsigned int x = ~0;

    unsigned int y = ~0;

    unsigned int z = ~0;



    unsigned int result = sha256Maj(x, y, z);

    EXPECT_EQ(result, ~0);

}



TEST_F(Sha256MajTest_1629, BoundaryConditions_MixedValues_1629) {

    unsigned int x = 0b10101010;

    unsigned int y = 0b01010101;

    unsigned int z = 0b11110000;



    unsigned int result = sha256Maj(x, y, z);

    unsigned int expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha256MajTest_1629, ExceptionalCases_NoExceptionExpected_1629) {

    // Since sha256Maj is a simple bitwise operation, it should not throw any exceptions.

    unsigned int x = 0b11110000;

    unsigned int y = 0b10101010;

    unsigned int z = 0b00001111;



    EXPECT_NO_THROW(sha256Maj(x, y, z));

}
