#include <gtest/gtest.h>
#include <string>
#include <cstdint>

// Include the header under test
#include "exiv2/types.hpp"

// Test toString with various integral types
TEST(ToStringTest_34, IntPositive_34) {
  int val = 42;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "42");
}

TEST(ToStringTest_34, IntZero_34) {
  int val = 0;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "0");
}

TEST(ToStringTest_34, IntNegative_34) {
  int val = -123;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "-123");
}

TEST(ToStringTest_34, UnsignedInt_34) {
  unsigned int val = 100u;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "100");
}

TEST(ToStringTest_34, LongValue_34) {
  long val = 999999L;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "999999");
}

TEST(ToStringTest_34, LongNegativeValue_34) {
  long val = -999999L;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "-999999");
}

TEST(ToStringTest_34, Int16_34) {
  int16_t val = 32767;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "32767");
}

TEST(ToStringTest_34, Int16Min_34) {
  int16_t val = -32768;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "-32768");
}

TEST(ToStringTest_34, Uint16Max_34) {
  uint16_t val = 65535;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "65535");
}

TEST(ToStringTest_34, Int32Max_34) {
  int32_t val = 2147483647;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "2147483647");
}

TEST(ToStringTest_34, Int64Value_34) {
  int64_t val = 1234567890123LL;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "1234567890123");
}

TEST(ToStringTest_34, Uint64Value_34) {
  uint64_t val = 18446744073709551615ULL;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "18446744073709551615");
}

TEST(ToStringTest_34, BoolTrue_34) {
  bool val = true;
  std::string result = Exiv2::toString(val);
  // bool is integral; expect "1" or "true" depending on implementation
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, BoolFalse_34) {
  bool val = false;
  std::string result = Exiv2::toString(val);
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, CharValue_34) {
  char val = 'A';
  std::string result = Exiv2::toString(val);
  // char is integral, could be "65" or "A" depending on implementation
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, FloatValue_34) {
  float val = 3.14f;
  std::string result = Exiv2::toString(val);
  // Float is not integral, so it goes through the non-integral path
  EXPECT_FALSE(result.empty());
  // Should contain "3.14" or similar representation
  EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(ToStringTest_34, DoubleValue_34) {
  double val = 2.71828;
  std::string result = Exiv2::toString(val);
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("2.71"), std::string::npos);
}

TEST(ToStringTest_34, DoubleNegativeValue_34) {
  double val = -1.5;
  std::string result = Exiv2::toString(val);
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("-1.5"), std::string::npos);
}

TEST(ToStringTest_34, DoubleZero_34) {
  double val = 0.0;
  std::string result = Exiv2::toString(val);
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, StringValue_34) {
  std::string val = "hello world";
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "hello world");
}

TEST(ToStringTest_34, EmptyString_34) {
  std::string val = "";
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "");
}

TEST(ToStringTest_34, UnsignedChar_34) {
  unsigned char val = 255;
  std::string result = Exiv2::toString(val);
  // unsigned char is integral
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, SignedCharNegative_34) {
  signed char val = -1;
  std::string result = Exiv2::toString(val);
  EXPECT_FALSE(result.empty());
}

TEST(ToStringTest_34, IntOne_34) {
  int val = 1;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "1");
}

TEST(ToStringTest_34, IntMinusOne_34) {
  int val = -1;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "-1");
}

TEST(ToStringTest_34, LargeUnsigned_34) {
  unsigned long long val = 0;
  std::string result = Exiv2::toString(val);
  EXPECT_EQ(result, "0");
}
