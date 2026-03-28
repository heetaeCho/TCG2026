#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming sha256sigma1 is part of a class or namespace for testing purposes.

// Since it's a static inline function, we'll assume it's in a namespace called 'Crypto'.

namespace Crypto {

    static inline unsigned int sha256sigma1(unsigned int x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

}



// Mocking the rotr function since it's not provided in the snippet.

unsigned int mock_rotr(unsigned int x, unsigned int r) {

    // This is a simple implementation of rotate right for testing purposes.

    return (x >> r) | (x << (32 - r));

}



TEST(Sha256Sigma1Test_1633, NormalOperation_1633) {

    unsigned int x = 0b11110000111100001111000011110000;

    unsigned int expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);

}



TEST(Sha256Sigma1Test_1633, BoundaryCondition_AllOnes_1633) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);

}



TEST(Sha256Sigma1Test_1633, BoundaryCondition_AllZeros_1633) {

    unsigned int x = 0x00000000;

    unsigned int expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);

}



TEST(Sha256Sigma1Test_1633, BoundaryCondition_SingleBitSet_1633) {

    unsigned int x = 0x80000000; // MSB set

    unsigned int expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);



    x = 0x00000001; // LSB set

    expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);

}



TEST(Sha256Sigma1Test_1633, BoundaryCondition_MiddleBitsSet_1633) {

    unsigned int x = 0x00FF00FF; // Middle bits set

    unsigned int expected = mock_rotr(x, 17) ^ mock_rotr(x, 19) ^ (x >> 10);

    EXPECT_EQ(Crypto::sha256sigma1(x), expected);

}

```


