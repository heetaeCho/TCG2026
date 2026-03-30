// File: fill_bits_from_tests_334.cpp
#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_random_integer_helpers.hpp"

using Catch::Detail::fillBitsFrom;

// A simple fixed-output generator that satisfies the interface:
// - typedef result_type
// - static constexpr min() == 0
// - static constexpr max() == (result_type)-1
// - operator() returns a value within [min, max]
template <typename R>
struct FixedGen {
  using result_type = R;

  explicit FixedGen(R v) : value(v) {}

  static constexpr result_type min() { return static_cast<result_type>(0); }
  static constexpr result_type max() { return static_cast<result_type>(-1); }

  result_type operator()() { return value; }

  R value;
};

// ---------- Tests ----------

// Normal operation: when generator returns 0, result should be 0 for any TargetType
TEST(FillBitsFromTest_334, ReturnsZeroWhenSourceIsZero_334) {
  FixedGen<uint64_t> gen64(0ull);

  EXPECT_EQ(fillBitsFrom<uint8_t>(gen64),  static_cast<uint8_t>(0));
  EXPECT_EQ(fillBitsFrom<uint16_t>(gen64), static_cast<uint16_t>(0));
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen64), static_cast<uint32_t>(0));
}

// Boundary: when generator returns its maximum, the result should be all 1s
// in the TargetType (since the highest bits of all-ones are all-ones).
TEST(FillBitsFromTest_334, ReturnsAllOnesWhenSourceIsMax_334) {
  FixedGen<uint64_t> gen64(~0ull);
  FixedGen<uint32_t> gen32(~0u);

  // Smaller-than-generator target
  EXPECT_EQ(fillBitsFrom<uint8_t>(gen64),  static_cast<uint8_t>(0xFFu));
  EXPECT_EQ(fillBitsFrom<uint16_t>(gen64), static_cast<uint16_t>(0xFFFFu));
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen64), static_cast<uint32_t>(0xFFFFFFFFu));

  // Equal-size target
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen32), static_cast<uint32_t>(0xFFFFFFFFu));
}

// Normal operation: equal sizes -> no shifting, value should pass through unchanged
TEST(FillBitsFromTest_334, EqualSizePassThrough_334) {
  FixedGen<uint32_t> gen32(0x89ABCDEFu);
  // generated_bits == return_bits -> shift by 0
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen32), static_cast<uint32_t>(0x89ABCDEFu));
}

// Normal operation with a patterned source value, taking the high bits
TEST(FillBitsFromTest_334, TakesHighBitsForSmallerTarget_334) {
  // Patterned 64-bit value
  FixedGen<uint64_t> gen64(0x0123456789ABCDEFull);

  // For uint8_t target, expect the top 8 bits of the 64-bit value: 0x01
  EXPECT_EQ(fillBitsFrom<uint8_t>(gen64), static_cast<uint8_t>(0x01u));

  // For uint16_t target, expect the top 16 bits: 0x0123
  EXPECT_EQ(fillBitsFrom<uint16_t>(gen64), static_cast<uint16_t>(0x0123u));

  // For uint32_t target from 64-bit generator, expect top 32 bits: 0x01234567
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen64), static_cast<uint32_t>(0x01234567u));
}

// Boundary: mixed sizes with edge-placed set bits to ensure correct shift amount
TEST(FillBitsFromTest_334, CorrectShiftAmountOnEdgePatterns_334) {
  // Only the highest bit set in 64-bit
  FixedGen<uint64_t> gen_high1(1ull << 63);
  // Only bit 63 contributes to the high bits window
  EXPECT_EQ(fillBitsFrom<uint8_t>(gen_high1),  static_cast<uint8_t>(0x80u >> 0)); // 0x80 >> 0 == 0x80 in top byte window -> 0x80 after cast
  EXPECT_EQ(fillBitsFrom<uint16_t>(gen_high1), static_cast<uint16_t>(0x8000u));
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen_high1), static_cast<uint32_t>(0x80000000u));

  // Highest 32 bits set, lowest 32 clear
  FixedGen<uint64_t> gen_hi32(0xFFFFFFFF00000000ull);
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen_hi32), static_cast<uint32_t>(0xFFFFFFFFu));
  EXPECT_EQ(fillBitsFrom<uint16_t>(gen_hi32), static_cast<uint16_t>(0xFFFFu));
  EXPECT_EQ(fillBitsFrom<uint8_t>(gen_hi32),  static_cast<uint8_t>(0xFFu));
}

// Sanity: works with another equal-size generator/result_type pair
TEST(FillBitsFromTest_334, EqualSizeWithDifferentPattern_334) {
  FixedGen<uint32_t> gen32(0x13579BDFu);
  EXPECT_EQ(fillBitsFrom<uint32_t>(gen32), static_cast<uint32_t>(0x13579BDFu));
}

// Note: The following compile-time constraints are enforced by static_asserts
// in the implementation and cannot be tested as runtime "failing" tests:
// - TargetType must be unsigned
// - Generator::min() == 0 && Generator::max() == (result_type)-1
// - sizeof(Generator::result_type) >= sizeof(TargetType)
// These tests ensure *successful* compilation with conforming types and
// validate observable behavior across normal and boundary conditions.
