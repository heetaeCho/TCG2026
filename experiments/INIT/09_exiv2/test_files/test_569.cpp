// SPDX-License-Identifier: GPL-2.0-or-later
// File: blockmap_populate_test_569.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Exiv2 headers (BlockMap is part of basicio)
#include "basicio.hpp"

namespace {

using Exiv2::BlockMap;

// Helper to build a byte buffer with stable storage.
static std::vector<Exiv2::byte> MakeBytes(std::initializer_list<unsigned int> vals) {
  std::vector<Exiv2::byte> out;
  out.reserve(vals.size());
  for (auto v : vals) out.push_back(static_cast<Exiv2::byte>(v & 0xFFu));
  return out;
}

class BlockMapTest_569 : public ::testing::Test {};

TEST_F(BlockMapTest_569, DefaultState_IsNone_569) {
  BlockMap bm;
  EXPECT_TRUE(bm.isNone());
  EXPECT_FALSE(bm.isKnown());
  EXPECT_EQ(bm.getSize(), 0u);

  const auto data = bm.getData();
  EXPECT_TRUE(data.empty());
}

TEST_F(BlockMapTest_569, Populate_CopiesBytesAndSetsSize_569) {
  BlockMap bm;
  const auto src = MakeBytes({0x01, 0x02, 0x00, 0xFE, 0xFF});

  bm.populate(src.data(), src.size());

  EXPECT_EQ(bm.getSize(), src.size());

  const auto data = bm.getData();
  ASSERT_EQ(data.size(), src.size());
  EXPECT_TRUE(std::equal(data.begin(), data.end(), src.begin(), src.end()));

  // Observable state: should no longer be "none".
  EXPECT_FALSE(bm.isNone());
  // Observable state: "known" is distinct from "memory"; populate should not mark known.
  EXPECT_FALSE(bm.isKnown());
}

TEST_F(BlockMapTest_569, Populate_WithZeroLength_ResultsInEmptyData_569) {
  BlockMap bm;

  // Boundary: zero length. Use nullptr to avoid needing a valid pointer.
  bm.populate(nullptr, 0);

  EXPECT_EQ(bm.getSize(), 0u);
  const auto data = bm.getData();
  EXPECT_TRUE(data.empty());

  // Still should not be "known" after populate with 0 bytes.
  EXPECT_FALSE(bm.isKnown());
}

TEST_F(BlockMapTest_569, Populate_OverridesPreviousContent_569) {
  BlockMap bm;

  const auto first = MakeBytes({0x10, 0x11, 0x12});
  bm.populate(first.data(), first.size());

  ASSERT_EQ(bm.getSize(), first.size());
  ASSERT_EQ(bm.getData().size(), first.size());

  const auto second = MakeBytes({0xAA, 0xBB, 0xCC, 0xDD});
  bm.populate(second.data(), second.size());

  EXPECT_EQ(bm.getSize(), second.size());
  const auto data = bm.getData();
  ASSERT_EQ(data.size(), second.size());
  EXPECT_TRUE(std::equal(data.begin(), data.end(), second.begin(), second.end()));

  EXPECT_FALSE(bm.isNone());
  EXPECT_FALSE(bm.isKnown());
}

TEST_F(BlockMapTest_569, Populate_DoesNotMutateSourceBuffer_569) {
  BlockMap bm;

  auto src = MakeBytes({0x01, 0x02, 0x03, 0x04});
  const auto snapshot = src;  // keep original

  bm.populate(src.data(), src.size());

  // The public interface doesn't expose internals; we can at least ensure the
  // provided source buffer contents are unchanged by the call.
  EXPECT_EQ(src, snapshot);

  // And the BlockMap data matches what was provided.
  const auto data = bm.getData();
  ASSERT_EQ(data.size(), snapshot.size());
  EXPECT_TRUE(std::equal(data.begin(), data.end(), snapshot.begin(), snapshot.end()));
}

}  // namespace