// File: util/coding_varintlength_test.cc

#include <cstdint>
#include <vector>
#include "gtest/gtest.h"

// Prefer including the public declaration if available in your codebase:
// #include "util/coding.h"
// For completeness in this isolated snippet, declare the function as used:
namespace leveldb {
int VarintLength(uint64_t v);
}

using leveldb::VarintLength;

namespace {

// Normal operation + initial boundary checks (0..127 -> 1 byte; 128 -> 2 bytes)
TEST(VarintLengthTest_445, HandlesSmallValuesAndBoundaries_445) {
  // A handful of representative small values all requiring length 1
  EXPECT_EQ(1, VarintLength(0ULL));
  EXPECT_EQ(1, VarintLength(1ULL));
  EXPECT_EQ(1, VarintLength(42ULL));
  EXPECT_EQ(1, VarintLength(127ULL));  // max with 1 byte

  // Boundary: first value that should require 2 bytes
  EXPECT_EQ(2, VarintLength(128ULL));
  // A few values within the 2-byte range
  EXPECT_EQ(2, VarintLength(255ULL));
  EXPECT_EQ(2, VarintLength(16383ULL)); // max with 2 bytes
}

// Exhaustive boundary checks across all 7-bit thresholds up to uint64_t max
TEST(VarintLengthTest_445, HandlesLargerBoundariesUpToUint64Max_445) {
  // Each pair is {value, expected_length}
  // Thresholds are at 2^(7*k): [0..2^7-1] -> 1, [2^7..2^14-1] -> 2, ..., up to 10 bytes for uint64_t.
  const std::vector<std::pair<uint64_t, int>> cases = {
      // 1-byte range
      {0ULL, 1}, {127ULL, 1},
      // 2-byte range
      {128ULL, 2}, {255ULL, 2}, {16383ULL, 2},
      // 3-byte range
      {16384ULL, 3}, {2097151ULL, 3},
      // 4-byte range
      {2097152ULL, 4}, {268435455ULL, 4},
      // 5-byte range
      {268435456ULL, 5}, {34359738367ULL, 5},
      // 6-byte range
      {34359738368ULL, 6}, {4398046511103ULL, 6},
      // 7-byte range
      {4398046511104ULL, 7}, {562949953421311ULL, 7},
      // 8-byte range
      {562949953421312ULL, 8}, {72057594037927935ULL, 8},
      // 9-byte range
      {72057594037927936ULL, 9}, {9223372036854775807ULL, 9},
      // 10-byte range (covers the full uint64_t domain)
      {9223372036854775808ULL, 10}, {18446744073709551615ULL, 10},
  };

  for (const auto& [value, expected] : cases) {
    EXPECT_EQ(expected, VarintLength(value)) << "value=" << value;
  }
}

// Property-style check: length should be non-decreasing as value increases.
// We probe around each threshold to ensure the step-up only increases length, never decreases it.
TEST(VarintLengthTest_445, MonotonicNonDecreasing_445) {
  // Probe key points: just below, at, and just above thresholds 2^(7*k)
  auto check_window = [](uint64_t center) {
    // Use a tight window around 'center' while avoiding underflow.
    for (int64_t delta = -2; delta <= 2; ++delta) {
      if (delta < 0 && center < static_cast<uint64_t>(-delta)) continue;
      uint64_t a = center + delta;
      uint64_t b = a + 1;
      if (b < a) continue; // overflow guard
      EXPECT_LE(VarintLength(a), VarintLength(b)) << "a=" << a << ", b=" << b;
    }
  };

  // Cover thresholds for k = 0..9 (2^(7*k))
  uint64_t t = 1ULL; // 2^(7*0) = 1
  for (int k = 0; k <= 9; ++k) {
    // threshold value is 2^(7*k); for k=0, t==1 (the first non-zero threshold);
    // we still probe windows around it and later ones.
    check_window(t);
    // Guard next multiplication from overflow (stop when next shift would exceed 64 bits)
    if (k < 9) {
      // advance t *= 2^7
      t <<= 7;
    }
  }

  // Also probe near extremes explicitly
  check_window(0ULL);
  check_window(127ULL);
  check_window(128ULL);
  check_window(18446744073709551615ULL - 2ULL);
}

}  // namespace
