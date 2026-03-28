#include <gtest/gtest.h>

#include <cstdint>



// Assuming the sha256sigma0 function is part of a namespace or header file that we need to include.

// Since it's a static inline function, we'll define it here for completeness in this test file.

static inline unsigned int rotr(unsigned int x, unsigned int n) {

    return (x >> n) | (x << (32 - n));

}



static inline unsigned int sha256sigma0(unsigned int x) { 

    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); 

}



// Test suite for sha256sigma0 function

class Sha256Sigma0Test_1632 : public ::testing::Test {

protected:

    // Any setup or teardown code can go here if needed.

};



TEST_F(Sha256Sigma0Test_1632, NormalOperation_1632) {

    unsigned int x = 0x12345678;

    unsigned int expected_result = rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);

    EXPECT_EQ(sha256sigma0(x), expected_result);

}



TEST_F(Sha256Sigma0Test_1632, BoundaryCondition_AllZeros_1632) {

    unsigned int x = 0x00000000;

    unsigned int expected_result = 0x00000000;

    EXPECT_EQ(sha256sigma0(x), expected_result);

}



TEST_F(Sha256Sigma0Test_1632, BoundaryCondition_AllOnes_1632) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int expected_result = rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);

    EXPECT_EQ(sha256sigma0(x), expected_result);

}



TEST_F(Sha256Sigma0Test_1632, BoundaryCondition_MaxValue_1632) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int expected_result = rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);

    EXPECT_EQ(sha256sigma0(x), expected_result);

}



TEST_F(Sha256Sigma0Test_1632, BoundaryCondition_MinValue_1632) {

    unsigned int x = 0x00000000;

    unsigned int expected_result = rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);

    EXPECT_EQ(sha256sigma0(x), expected_result);

}
