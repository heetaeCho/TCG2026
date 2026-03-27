// File: re2_parse_float_test_273.cc

#include <gtest/gtest.h>
#include <cstddef>
#include <cmath>

// Forward declaration of the function under test.
// We declare only the visible interface we need (no peeking at internals).
namespace re2 { namespace re2_internal {
bool Parse(const char* str, size_t n, float* dest);
}}

// A simple test fixture in case future cases need shared setup/teardown.
class ParseFloatTest_273 : public ::testing::Test {};

// === Normal operation ===

TEST_F(ParseFloatTest_273, ParsesSimpleDecimal_273) {
  const char* s = "3.14";
  float out = 0.0f;
  ASSERT_TRUE(re2::re2_internal::Parse(s, 4, &out));
  EXPECT_NEAR(out, 3.14f, 1e-6f);
}

TEST_F(ParseFloatTest_273, ParsesInteger_273) {
  const char* s = "42";
  float out = -1.0f;
  ASSERT_TRUE(re2::re2_internal::Parse(s, 2, &out));
  EXPECT_FLOAT_EQ(out, 42.0f);
}

TEST_F(ParseFloatTest_273, ParsesScientificNotation_273) {
  const char* s = "1e3";
  float out = 0.0f;
  ASSERT_TRUE(re2::re2_internal::Parse(s, 3, &out));
  EXPECT_FLOAT_EQ(out, 1000.0f);
}

TEST_F(ParseFloatTest_273, ParsesNegative_273) {
  const char* s = "-0.5";
  float out = 0.0f;
  ASSERT_TRUE(re2::re2_internal::Parse(s, 4, &out));
  EXPECT_NEAR(out, -0.5f, 1e-6f);
}

// === Boundary conditions ===

TEST_F(ParseFloatTest_273, ZeroLengthReturnsFalse_273) {
  const char* s = "";
  float out = 123.0f;  // Should remain unchanged on failure
  EXPECT_FALSE(re2::re2_internal::Parse(s, 0, &out));
  EXPECT_FLOAT_EQ(out, 123.0f);
}

// Using n smaller than the underlying buffer size should parse only the first n chars.
TEST_F(ParseFloatTest_273, UsesProvidedLengthOnly_273) {
  const char* s = "12junk";
  float out = 0.0f;
  // Only "12" should be considered; it is valid.
  ASSERT_TRUE(re2::re2_internal::Parse(s, 2, &out));
  EXPECT_FLOAT_EQ(out, 12.0f);
}

// === Exceptional / error cases (observable through the interface) ===

TEST_F(ParseFloatTest_273, InvalidInputReturnsFalseAndDoesNotWrite_273) {
  const char* s = "abc";
  float out = 7.0f;  // Sentinel
  EXPECT_FALSE(re2::re2_internal::Parse(s, 3, &out));
  // On failure, output parameter must not be modified.
  EXPECT_FLOAT_EQ(out, 7.0f);
}

TEST_F(ParseFloatTest_273, LeftoverJunkReturnsFalse_273) {
  const char* s = "1.2x";
  float out = -9.0f;  // Sentinel
  EXPECT_FALSE(re2::re2_internal::Parse(s, 4, &out));
  EXPECT_FLOAT_EQ(out, -9.0f);
}

// A very large exponent should overflow float parsing in typical C libraries,
// causing errno to be set inside the function and a false return.
TEST_F(ParseFloatTest_273, OverflowTriggersFalse_273) {
  const char* s = "1e1000";
  float out = 0.0f;
  EXPECT_FALSE(re2::re2_internal::Parse(s, 6, &out));
  // No guarantee about out on failure; do not assert its value.
}

// === External interaction proxy (dest == nullptr) ===

TEST_F(ParseFloatTest_273, ReturnsTrueWhenDestIsNullForValidInput_273) {
  const char* s = "2.5";
  // Should succeed and not attempt to write through dest.
  EXPECT_TRUE(re2::re2_internal::Parse(s, 3, /*dest=*/nullptr));
}
