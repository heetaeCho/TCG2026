#include <gtest/gtest.h>

#include <cstdint>



// Assuming sha256Sigma1 is exposed in a header file for testing purposes.

unsigned int sha256Sigma1(unsigned int x);



class Sha256Sigma1Test : public ::testing::Test {

protected:

    // You can set up any common state here if necessary

};



TEST_F(Sha256Sigma1Test, NormalOperation_1631) {

    unsigned int input = 0x12345678;

    unsigned int expectedOutput = (rotr(input, 6) ^ rotr(input, 11) ^ rotr(input, 25));

    EXPECT_EQ(sha256Sigma1(input), expectedOutput);

}



TEST_F(Sha256Sigma1Test, BoundaryCondition_Zero_1631) {

    unsigned int input = 0x0;

    unsigned int expectedOutput = (rotr(input, 6) ^ rotr(input, 11) ^ rotr(input, 25));

    EXPECT_EQ(sha256Sigma1(input), expectedOutput);

}



TEST_F(Sha256Sigma1Test, BoundaryCondition_MaxUint_1631) {

    unsigned int input = UINT32_MAX;

    unsigned int expectedOutput = (rotr(input, 6) ^ rotr(input, 11) ^ rotr(input, 25));

    EXPECT_EQ(sha256Sigma1(input), expectedOutput);

}



// Since the function is deterministic and does not interact with external systems,

// there are no exceptional or error cases to test.



// Helper function for rotate right

unsigned int rotr(unsigned int value, unsigned int shift) {

    return (value >> shift) | (value << (32 - shift));

}

```


