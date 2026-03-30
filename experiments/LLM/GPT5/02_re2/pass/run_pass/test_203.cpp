// File: parse_double_float_test_203.cc

#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>
#include <limits>
#include <string>

// Directly include the implementation unit so we can access the internal-linkage function.
// This is a common technique for testing internal/static functions.
#include "TestProjects/re2/util/pcre.cc"

using re2::parse_double_float;

class ParseDoubleFloatTest_203 : public ::testing::Test {};

// ----- Normal operation -----

TEST_F(ParseDoubleFloatTest_203, ParsesSimpleDouble_203) {
  const std::string s = "3.14159";
  double out = 0.0;
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, strtod(s.c_str(), nullptr));
}

TEST_F(ParseDoubleFloatTest_203, ParsesSimpleFloat_203) {
  const std::string s = "2.71828";
  float out = 0.0f;
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/true, &out));
  // Compare against strtof for the same input
  EXPECT_FLOAT_EQ(out, strtof(s.c_str(), nullptr));
}

TEST_F(ParseDoubleFloatTest_203, ParsesSignedExponentDouble_203) {
  const std::string s = "-2.5e3";
  double out = 0.0;
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, strtod(s.c_str(), nullptr));
}

TEST_F(ParseDoubleFloatTest_203, LeadingWhitespaceAllowed_203) {
  const std::string s = "   42";
  double out = 0.0;
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, 42.0);
}

// dest == NULL: should succeed on valid input without writing
TEST_F(ParseDoubleFloatTest_203, NullDestReturnsTrueOnValidInput_Double_203) {
  const std::string s = "1.25";
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, /*dest=*/nullptr));
}

TEST_F(ParseDoubleFloatTest_203, NullDestReturnsTrueOnValidInput_Float_203) {
  const std::string s = "1.25";
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/true, /*dest=*/nullptr));
}

// ----- Boundary conditions -----

TEST_F(ParseDoubleFloatTest_203, ZeroLengthIsFalse_203) {
  const char* s = "";
  double out = -1.0;
  EXPECT_FALSE(parse_double_float(s, /*n=*/0, /*isfloat=*/false, &out));
  // Out should remain unchanged (observable effect)
  EXPECT_DOUBLE_EQ(out, -1.0);
}

// kMaxLength is 200; n >= 200 should fail, n == 199 should be okay
TEST_F(ParseDoubleFloatTest_203, LengthAtLimitMinusOneSucceeds_203) {
  std::string s(199, '0');  // "000...0" (199 chars)
  double out = 123.0;
  ASSERT_TRUE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, 0.0);
}

TEST_F(ParseDoubleFloatTest_203, LengthAtLimitFails_203) {
  std::string s(200, '0');  // length == 200 -> should fail early
  double out = 123.0;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, 123.0);  // unchanged
}

// Trailing spaces produce leftover unparsed characters -> false
TEST_F(ParseDoubleFloatTest_203, TrailingWhitespaceIsRejected_203) {
  const std::string s = "42   ";
  double out = -7.0;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, -7.0);  // unchanged
}

// Non-numeric junk after a valid number -> false
TEST_F(ParseDoubleFloatTest_203, TrailingJunkIsRejected_203) {
  const std::string s = "123abc";
  float out = -9.0f;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/true, &out));
  EXPECT_FLOAT_EQ(out, -9.0f);  // unchanged
}

// ----- Exceptional / error cases that are observable via errno in the callee -----

// Very large exponent: overflow -> errno set by strtod, function returns false
TEST_F(ParseDoubleFloatTest_203, DoubleOverflowIsRejected_203) {
  const std::string s = "1e4000";  // should overflow double
  double out = 0.0;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, 0.0);  // unchanged on failure
}

// Very small exponent: underflow -> errno set by strtod/strtof, function returns false
TEST_F(ParseDoubleFloatTest_203, DoubleUnderflowIsRejected_203) {
  const std::string s = "1e-5000";  // should underflow double
  double out = 1.0;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/false, &out));
  EXPECT_DOUBLE_EQ(out, 1.0);  // unchanged on failure
}

TEST_F(ParseDoubleFloatTest_203, FloatOverflowIsRejected_203) {
  const std::string s = "1e1000";  // should overflow float
  float out = 0.0f;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/true, &out));
  EXPECT_FLOAT_EQ(out, 0.0f);  // unchanged on failure
}

TEST_F(ParseDoubleFloatTest_203, FloatUnderflowIsRejected_203) {
  const std::string s = "1e-1000";  // should underflow float
  float out = 1.0f;
  EXPECT_FALSE(parse_double_float(s.c_str(), s.size(), /*isfloat=*/true, &out));
  EXPECT_FLOAT_EQ(out, 1.0f);  // unchanged on failure
}
