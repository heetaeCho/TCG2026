#include <gtest/gtest.h>

#include "Decrypt.cc"



class Sha256ChTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up any necessary state before each test.

    }



    void TearDown() override {

        // Clean up any necessary state after each test.

    }

};



TEST_F(Sha256ChTest_1628, NormalOperation_1628) {

    unsigned int x = 0b11110000;

    unsigned int y = 0b10101010;

    unsigned int z = 0b00001111;

    unsigned int expected = 0b00000010; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, AllOnes_1628) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int y = 0xFFFFFFFF;

    unsigned int z = 0xFFFFFFFF;

    unsigned int expected = 0xFFFFFFFF; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, AllZeros_1628) {

    unsigned int x = 0x00000000;

    unsigned int y = 0x00000000;

    unsigned int z = 0x00000000;

    unsigned int expected = 0x00000000; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, XAndYAllOnesZAllZeros_1628) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int y = 0xFFFFFFFF;

    unsigned int z = 0x00000000;

    unsigned int expected = 0x00000000; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, XAndYAllZerosZAllOnes_1628) {

    unsigned int x = 0x00000000;

    unsigned int y = 0x00000000;

    unsigned int z = 0xFFFFFFFF;

    unsigned int expected = 0xFFFFFFFF; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, XAllOnesYAndZAlternating_1628) {

    unsigned int x = 0xFFFFFFFF;

    unsigned int y = 0xAAAAAAAA;

    unsigned int z = 0x55555555;

    unsigned int expected = 0xAAAAAAAA; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}



TEST_F(Sha256ChTest_1628, XAllZerosYAndZAlternating_1628) {

    unsigned int x = 0x00000000;

    unsigned int y = 0xAAAAAAAA;

    unsigned int z = 0x55555555;

    unsigned int expected = 0x55555555; // (x & y) ^ (~x & z)

    EXPECT_EQ(sha256Ch(x, y, z), expected);

}
