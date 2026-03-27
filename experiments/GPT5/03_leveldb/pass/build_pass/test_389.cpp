// File: block_handle_set_offset_test_389.cc
#include <cstdint>
#include "gtest/gtest.h"

// Use the header as provided in the prompt.
#include "table/format.h"

using ::testing::Test;

namespace leveldb {

// Fixture kept minimal to respect black-box constraints.
class BlockHandleTest_389 : public Test {};

TEST_F(BlockHandleTest_389, SetOffset_ReflectsThroughGetter_389) {
  BlockHandle h;
  const uint64_t value = 123456789ULL;
  h.set_offset(value);

  // Observable behavior via the public getter
  EXPECT_EQ(h.offset(), value);
}

TEST_F(BlockHandleTest_389, SetOffset_Zero_389) {
  BlockHandle h;
  const uint64_t value = 0ULL;
  h.set_offset(value);

  EXPECT_EQ(h.offset(), value);
}

TEST_F(BlockHandleTest_389, SetOffset_MaxMinusOne_389) {
  BlockHandle h;
  // Avoid assuming anything about sentinel usage for UINT64_MAX.
  const uint64_t value = std::numeric_limits<uint64_t>::max() - 1ULL;
  h.set_offset(value);

  EXPECT_EQ(h.offset(), value);
}

TEST_F(BlockHandleTest_389, SetOffset_LastWriteWins_389) {
  BlockHandle h;

  const uint64_t first  = 42ULL;
  const uint64_t second = 9001ULL;
  const uint64_t third  = 7777777ULL;

  h.set_offset(first);
  h.set_offset(second);
  h.set_offset(third);

  // Only verify what is observable via the public API.
  EXPECT_EQ(h.offset(), third);
}

}  // namespace leveldb
