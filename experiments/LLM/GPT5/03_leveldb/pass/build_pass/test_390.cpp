// File: blockhandle_size_test_390.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

#include "table/format.h"  // provides leveldb::BlockHandle

using leveldb::BlockHandle;

// [390] Normal operation: size reflects the most recently set value.
TEST(BlockHandleSizeTest_390, SizeReturnsValuePreviouslySet_390) {
  BlockHandle h;
  h.set_size(123u);
  EXPECT_EQ(h.size(), 123u);
}

// [390] Boundary: size set to 0 should be observable as 0.
TEST(BlockHandleSizeTest_390, SizeZero_390) {
  BlockHandle h;
  h.set_size(0u);
  EXPECT_EQ(h.size(), 0u);
}

// [390] Boundary: size set to max uint64_t should be observable unchanged.
TEST(BlockHandleSizeTest_390, SizeMaxUint64_390) {
  BlockHandle h;
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  h.set_size(kMax);
  EXPECT_EQ(h.size(), kMax);
}

// [390] Independence from other fields: modifying offset must not affect size().
TEST(BlockHandleSizeTest_390, SizeUnaffectedByOffsetChanges_390) {
  BlockHandle h;
  h.set_size(4096u);
  h.set_offset(777u);  // Exercise another public mutator
  EXPECT_EQ(h.size(), 4096u);
}

// [390] Const-correctness & copy behavior: reading size() from const object and after copy.
TEST(BlockHandleSizeTest_390, SizeConstAndCopy_390) {
  BlockHandle h;
  h.set_size(555u);

  const BlockHandle& cref = h;  // const view
  EXPECT_EQ(cref.size(), 555u);

  BlockHandle copy = h;         // copy via public semantics
  EXPECT_EQ(copy.size(), 555u);
}
