#include <gtest/gtest.h>

#include "Decrypt.cc"  // Assuming md5Round1 is in this file



// Test fixture class for md5Round1

class Md5Round1Test_1618 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



// Normal operation test case

TEST_F(Md5Round1Test_1618, NormalOperation_1618) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9abcdef0;

    unsigned long c = 0x23456789;

    unsigned long d = 0xabcd1234;

    unsigned long Xk = 0xfedcba09;

    unsigned long s = 5;

    unsigned long Ti = 0x10325476;



    unsigned long expected_result = b + rotateLeft((a + ((b & c) | (~b & d)) + Xk + Ti), s);

    EXPECT_EQ(md5Round1(a, b, c, d, Xk, s, Ti), expected_result);

}



// Boundary conditions test case

TEST_F(Md5Round1Test_1618, BoundaryConditions_1618) {

    unsigned long a = 0xFFFFFFFF;

    unsigned long b = 0x00000000;

    unsigned long c = 0xFFFFFFFF;

    unsigned long d = 0x00000000;

    unsigned long Xk = 0xFFFFFFFF;

    unsigned long s = 32; // Full rotation

    unsigned long Ti = 0x00000000;



    unsigned long expected_result = b + rotateLeft((a + ((b & c) | (~b & d)) + Xk + Ti), s);

    EXPECT_EQ(md5Round1(a, b, c, d, Xk, s, Ti), expected_result);

}



// Test case with zero values

TEST_F(Md5Round1Test_1618, ZeroValues_1618) {

    unsigned long a = 0x00000000;

    unsigned long b = 0x00000000;

    unsigned long c = 0x00000000;

    unsigned long d = 0x00000000;

    unsigned long Xk = 0x00000000;

    unsigned long s = 1;

    unsigned long Ti = 0x00000000;



    unsigned long expected_result = b + rotateLeft((a + ((b & c) | (~b & d)) + Xk + Ti), s);

    EXPECT_EQ(md5Round1(a, b, c, d, Xk, s, Ti), expected_result);

}



// Test case with maximum shift value

TEST_F(Md5Round1Test_1618, MaxShiftValue_1618) {

    unsigned long a = 0x12345678;

    unsigned long b = 0x9abcdef0;

    unsigned long c = 0x23456789;

    unsigned long d = 0xabcd1234;

    unsigned long Xk = 0xfedcba09;

    unsigned long s = 31; // Maximum shift before full rotation

    unsigned long Ti = 0x10325476;



    unsigned long expected_result = b + rotateLeft((a + ((b & c) | (~b & d)) + Xk + Ti), s);

    EXPECT_EQ(md5Round1(a, b, c, d, Xk, s, Ti), expected_result);

}
