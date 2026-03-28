// Decrypt_rotWord_unittest_1602.cc

#include <gtest/gtest.h>
#include <cstdint>

// Include the production implementation directly so we test the real function
// (it has internal linkage: static inline).
#include "Decrypt.cc"

class RotWordTest_1602 : public ::testing::Test {};

TEST_F(RotWordTest_1602, RotatesBytesLeftByOne_1602) {
  const unsigned int x = 0x12345678u;
  const unsigned int out = rotWord(x);
  EXPECT_EQ(out, 0x34567812u);
}

TEST_F(RotWordTest_1602, ZeroRemainsZero_1602) {
  EXPECT_EQ(rotWord(0u), 0u);
}

TEST_F(RotWordTest_1602, AllOnesRemainsAllOnes_1602) {
  EXPECT_EQ(rotWord(0xFFFFFFFFu), 0xFFFFFFFFu);
}

TEST_F(RotWordTest_1602, HandlesHighBitShiftOutCorrectly_1602) {
  // 0x80000000 -> bytes: 80 00 00 00, rotate left by 1 byte -> 00 00 00 80
  EXPECT_EQ(rotWord(0x80000000u), 0x00000080u);
}

TEST_F(RotWordTest_1602, RotatesLowByteIntoSecondByte_1602) {
  // 00 00 00 FF -> 00 00 FF 00
  EXPECT_EQ(rotWord(0x000000FFu), 0x0000FF00u);
}

TEST_F(RotWordTest_1602, FourApplicationsReturnOriginal_1602) {
  const unsigned int x = 0xA1B2C3D4u;
  unsigned int y = x;
  y = rotWord(y);
  y = rotWord(y);
  y = rotWord(y);
  y = rotWord(y);
  EXPECT_EQ(y, x);
}