// File: options_set_max_mem_test_13.cc
#include <gtest/gtest.h>
#include <limits>
#include "re2/re2.h"

using re2::RE2;

class OptionsMaxMemTest_13 : public ::testing::Test {};

// Normal operation: setting a typical positive value updates observable state.
TEST_F(OptionsMaxMemTest_13, SetMaxMemUpdatesValue_13) {
  RE2::Options opt;
  int64_t value = 1024;
  opt.set_max_mem(value);
  EXPECT_EQ(opt.max_mem(), value);
}

// Boundary: setting zero should be observable via the getter (no assumptions beyond interface).
TEST_F(OptionsMaxMemTest_13, SetMaxMemToZero_13) {
  RE2::Options opt;
  opt.set_max_mem(0);
  EXPECT_EQ(opt.max_mem(), 0);
}

// Boundary: setting to INT64_MAX is observable via the getter.
TEST_F(OptionsMaxMemTest_13, SetMaxMemToInt64Max_13) {
  RE2::Options opt;
  int64_t maxv = std::numeric_limits<int64_t>::max();
  opt.set_max_mem(maxv);
  EXPECT_EQ(opt.max_mem(), maxv);
}

// Exceptional/edge input (interface-observable): negative value behavior is verified only via public getter.
TEST_F(OptionsMaxMemTest_13, SetMaxMemToNegative_13) {
  RE2::Options opt;
  int64_t neg = -1;
  opt.set_max_mem(neg);
  EXPECT_EQ(opt.max_mem(), neg);
}

// Repeated calls: last call wins (verified through observable state only).
TEST_F(OptionsMaxMemTest_13, MultipleUpdatesLastWins_13) {
  RE2::Options opt;
  opt.set_max_mem(64);
  opt.set_max_mem(128);
  opt.set_max_mem(256);
  EXPECT_EQ(opt.max_mem(), 256);
}

// External interaction via another public API: Copy should preserve the observable max_mem.
TEST_F(OptionsMaxMemTest_13, CopyPreservesMaxMem_13) {
  RE2::Options src;
  RE2::Options dst;
  src.set_max_mem(4096);
  dst.Copy(src);
  EXPECT_EQ(dst.max_mem(), 4096);
}
