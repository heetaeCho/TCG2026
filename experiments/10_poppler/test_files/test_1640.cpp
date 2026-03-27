#include <gtest/gtest.h>



// Assuming that sha512Sigma1 is part of a class or namespace for testing purposes.

// Since it's a static inline function, we will wrap it in a simple struct for testing.

struct Sha512Operations {

    static uint64_t sha512Sigma1(uint64_t x) { return ::sha512Sigma1(x); }

};



TEST(Sha512Sigma1Test_1640, NormalOperation_1640) {

    uint64_t input = 0x123456789ABCDEF0;

    uint64_t expected_output = rotr(input, 14) ^ rotr(input, 18) ^ rotr(input, 41);

    EXPECT_EQ(Sha512Operations::sha512Sigma1(input), expected_output);

}



TEST(Sha512Sigma1Test_1640, BoundaryConditionZero_1640) {

    uint64_t input = 0;

    uint64_t expected_output = 0; // Any rotation or XOR of zero is zero.

    EXPECT_EQ(Sha512Operations::sha512Sigma1(input), expected_output);

}



TEST(Sha512Sigma1Test_1640, BoundaryConditionAllOnes_1640) {

    uint64_t input = 0xFFFFFFFFFFFFFFFF;

    uint64_t expected_output = rotr(input, 14) ^ rotr(input, 18) ^ rotr(input, 41);

    EXPECT_EQ(Sha512Operations::sha512Sigma1(input), expected_output);

}



TEST(Sha512Sigma1Test_1640, LargeInputValue_1640) {

    uint64_t input = 0xDEADBEEFDEADBEEF;

    uint64_t expected_output = rotr(input, 14) ^ rotr(input, 18) ^ rotr(input, 41);

    EXPECT_EQ(Sha512Operations::sha512Sigma1(input), expected_output);

}

```


