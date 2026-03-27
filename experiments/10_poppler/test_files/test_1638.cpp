#include <gtest/gtest.h>



// Assuming sha512Maj is part of a class or namespace that we need to mock or access.

// Since it's a static inline function, we will directly call it for testing.



class Sha512MajTest : public ::testing::Test {

protected:

    // If there were any setup or teardown needed, it would go here.

};



TEST_F(Sha512MajTest_1638, MajFunction_NormalOperation_1638) {

    uint64_t x = 0b11110000;

    uint64_t y = 0b10101010;

    uint64_t z = 0b00001111;



    uint64_t result = sha512Maj(x, y, z);

    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha512MajTest_1638, MajFunction_AllOnes_1638) {

    uint64_t x = 0xFFFFFFFFFFFFFFFF;

    uint64_t y = 0xFFFFFFFFFFFFFFFF;

    uint64_t z = 0xFFFFFFFFFFFFFFFF;



    uint64_t result = sha512Maj(x, y, z);

    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha512MajTest_1638, MajFunction_AllZeros_1638) {

    uint64_t x = 0;

    uint64_t y = 0;

    uint64_t z = 0;



    uint64_t result = sha512Maj(x, y, z);

    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha512MajTest_1638, MajFunction_MixedValues_1638) {

    uint64_t x = 0b1010101010101010101010101010101010101010101010101010101010101010;

    uint64_t y = 0b0101010101010101010101010101010101010101010101010101010101010101;

    uint64_t z = 0b1111000000001111000000001111000000001111000000001111000000001111;



    uint64_t result = sha512Maj(x, y, z);

    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}



TEST_F(Sha512MajTest_1638, MajFunction_BoundaryValues_1638) {

    uint64_t x = 0xFFFFFFFFFFFFFFFF;

    uint64_t y = 0x8000000000000000;

    uint64_t z = 0x7FFFFFFFFFFFFFFF;



    uint64_t result = sha512Maj(x, y, z);

    uint64_t expected = (x & y) ^ (x & z) ^ (y & z);



    EXPECT_EQ(result, expected);

}
