#include <gtest/gtest.h>



// Assuming rotr function is part of a class or namespace, for the sake of testing we will wrap it.

class DecryptUtils {

public:

    static uint64_t rotr(uint64_t x, uint64_t n) {

        return (x >> n) | (x << (64 - n));

    }

};



// Test fixture

class RotrTest_1636 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



// Normal operation tests

TEST_F(RotrTest_1636, RotateRightNormalOperation_1636) {

    uint64_t x = 0x123456789ABCDEF0;

    uint64_t n = 8;

    uint64_t expected = 0xF0123456789ABCDE;

    EXPECT_EQ(DecryptUtils::rotr(x, n), expected);

}



// Boundary conditions tests

TEST_F(RotrTest_1636, RotateRightZeroShift_1636) {

    uint64_t x = 0x123456789ABCDEF0;

    uint64_t n = 0;

    EXPECT_EQ(DecryptUtils::rotr(x, n), x);

}



TEST_F(RotrTest_1636, RotateRightFullShift_1636) {

    uint64_t x = 0x123456789ABCDEF0;

    uint64_t n = 64;

    EXPECT_EQ(DecryptUtils::rotr(x, n), x);

}



TEST_F(RotrTest_1636, RotateRightMaxShiftMinusOne_1636) {

    uint64_t x = 0x123456789ABCDEF0;

    uint64_t n = 63;

    uint64_t expected = 0x8F0123456789ABCD;

    EXPECT_EQ(DecryptUtils::rotr(x, n), expected);

}



// Exceptional or error cases (if observable through the interface)

// Since rotr is a simple bitwise operation, there are no exceptional/error cases to test.



```


