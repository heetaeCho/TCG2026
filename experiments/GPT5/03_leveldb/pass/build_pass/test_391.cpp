// blockhandle_size_test.cc
#include "table/format.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

using leveldb::BlockHandle;

TEST(BlockHandleTest_391, SetSizeReturnsSameViaGetter_391) {
  BlockHandle h;
  const uint64_t v = 123456789ULL;
  h.set_size(v);
  // Observable behavior: size() should reflect the last value set via set_size()
  EXPECT_EQ(v, h.size());
}

TEST(BlockHandleTest_391, SetSizeZeroBoundary_391) {
  BlockHandle h;
  const uint64_t v = 0ULL;
  h.set_size(v);
  EXPECT_EQ(v, h.size());
}

TEST(BlockHandleTest_391, SetSizeMaxUint64Boundary_391) {
  BlockHandle h;
  const uint64_t v = std::numeric_limits<uint64_t>::max();
  h.set_size(v);
  EXPECT_EQ(v, h.size());
}

TEST(BlockHandleTest_391, MultipleSetSizeLastWriteWins_391) {
  BlockHandle h;
  const uint64_t first = 1ULL;
  const uint64_t second = 42ULL;
  const uint64_t third = 9876543210ULL;

  h.set_size(first);
  EXPECT_EQ(first, h.size());   // after first set, getter reflects it

  h.set_size(second);
  EXPECT_EQ(second, h.size());  // subsequent set should overwrite prior value

  h.set_size(third);
  EXPECT_EQ(third, h.size());   // final set should be observable via getter
}
