// File: max_bytes_for_level_test_128.cc

#include <gtest/gtest.h>

// Pull in the function under test. Since it has internal linkage ("static")
// in the .cc, we include the .cc directly so the symbol is available here.
#include "db/version_set.cc"

#include "leveldb/options.h"

namespace {

// A small helper to get a default Options instance without relying on internals.
leveldb::Options MakeDefaultOptions() {
  leveldb::Options opt;  // Uses the provided default constructor from options.h
  return opt;
}

// Base size used by the implementation (treated as an observable constant from the interface).
// We avoid re-implementing logic; we only use explicit constants visible from the code snippet.
constexpr double kBaseBytes = 10.0 * 1048576.0;  // 10 MB in bytes

}  // namespace

// ------------------- Normal operation -------------------

TEST(MaxBytesForLevelTest_128, Level0_ReturnsBase_128) {
  // For level 0, validate it returns the documented/base size.
  leveldb::Options opt = MakeDefaultOptions();
  double bytes = leveldb::MaxBytesForLevel(&opt, /*level=*/0);
  EXPECT_DOUBLE_EQ(bytes, kBaseBytes);
}

TEST(MaxBytesForLevelTest_128, Level1_ReturnsBase_128) {
  // For level 1, validate it returns the same base size.
  leveldb::Options opt = MakeDefaultOptions();
  double bytes = leveldb::MaxBytesForLevel(&opt, /*level=*/1);
  EXPECT_DOUBLE_EQ(bytes, kBaseBytes);
}

TEST(MaxBytesForLevelTest_128, Level2_IsTenTimesBase_128) {
  // For level 2, validate it returns 10x the base.
  leveldb::Options opt = MakeDefaultOptions();
  double bytes = leveldb::MaxBytesForLevel(&opt, /*level=*/2);
  EXPECT_DOUBLE_EQ(bytes, kBaseBytes * 10.0);
}

TEST(MaxBytesForLevelTest_128, Level3_IsHundredTimesBase_128) {
  // For level 3, validate it returns 100x the base.
  leveldb::Options opt = MakeDefaultOptions();
  double bytes = leveldb::MaxBytesForLevel(&opt, /*level=*/3);
  EXPECT_DOUBLE_EQ(bytes, kBaseBytes * 100.0);
}

// ------------------- Boundary conditions -------------------

TEST(MaxBytesForLevelTest_128, NegativeLevel_TreatedAsBase_128) {
  // Levels <= 1 should not scale up; negative level should behave like base.
  leveldb::Options opt = MakeDefaultOptions();
  double bytes = leveldb::MaxBytesForLevel(&opt, /*level=*/-5);
  EXPECT_DOUBLE_EQ(bytes, kBaseBytes);
}

TEST(MaxBytesForLevelTest_128, MonotonicNonDecreasing_ForSmallRange_128) {
  // Sanity check monotonicity for a small range without asserting specific internals.
  leveldb::Options opt = MakeDefaultOptions();
  double prev = leveldb::MaxBytesForLevel(&opt, /*level=*/0);
  for (int level = 1; level <= 6; ++level) {
    double cur = leveldb::MaxBytesForLevel(&opt, level);
    EXPECT_LE(prev, cur) << "bytes(level=" << (level - 1)
                         << ")=" << prev << " > bytes(level=" << level
                         << ")=" << cur;
    prev = cur;
  }
}

// ------------------- Exceptional / robustness cases -------------------

TEST(MaxBytesForLevelTest_128, NullOptionsPointer_IsAccepted_AndMatchesDefault_128) {
  // The function does not dereference Options in the provided snippet.
  // Verify nullptr behaves the same as a default Options pointer.
  leveldb::Options opt = MakeDefaultOptions();
  int level = 2;

  double with_opt = leveldb::MaxBytesForLevel(&opt, level);
  double with_null = leveldb::MaxBytesForLevel(nullptr, level);

  EXPECT_DOUBLE_EQ(with_opt, with_null);
}

