#include <gtest/gtest.h>

#include <cstdint>



// Assuming sha512Sigma0 is part of a class or namespace for testing purposes.

// Since it's a static inline function, we can directly call it in our tests.



class Sha512Sigma0Test : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(Sha512Sigma0Test_1639, NormalOperation_1639) {

    uint64_t x = 0x123456789ABCDEF0;

    uint64_t expected = rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39);

    EXPECT_EQ(sha512Sigma0(x), expected);

}



TEST_F(Sha512Sigma0Test_1639, BoundaryCondition_Zero_1639) {

    uint64_t x = 0;

    uint64_t expected = 0;

    EXPECT_EQ(sha512Sigma0(x), expected);

}



TEST_F(Sha512Sigma0Test_1639, BoundaryCondition_MaxUint64_1639) {

    uint64_t x = UINT64_MAX;

    uint64_t expected = rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39);

    EXPECT_EQ(sha512Sigma0(x), expected);

}



TEST_F(Sha512Sigma0Test_1639, BoundaryCondition_PowerOfTwo_1639) {

    uint64_t x = 1ULL << 32; // Example power of two

    uint64_t expected = rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39);

    EXPECT_EQ(sha512Sigma0(x), expected);

}

```


