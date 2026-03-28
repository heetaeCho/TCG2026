// File: arena_test_85.cc
#include "util/arena.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>

using leveldb::Arena;

namespace {

// Simple helper to check that two [ptr, ptr+size) ranges do not overlap.
bool RangesDoNotOverlap(const char* p1, size_t s1, const char* p2, size_t s2) {
  const uintptr_t a1 = reinterpret_cast<uintptr_t>(p1);
  const uintptr_t b1 = a1 + s1;
  const uintptr_t a2 = reinterpret_cast<uintptr_t>(p2);
  const uintptr_t b2 = a2 + s2;
  return (b1 <= a2) || (b2 <= a1);
}

}  // namespace

class ArenaTest_85 : public ::testing::Test {
 protected:
  Arena arena_;
};

// Normal operation: allocating returns non-null and memory is writable.
TEST_F(ArenaTest_85, AllocateMemoryWritable_85) {
  const size_t n = 100;
  char* p = arena_.Allocate(n);
  ASSERT_NE(p, nullptr);

  // Write a simple pattern and verify.
  for (size_t i = 0; i < n; ++i) p[i] = static_cast<char>(i & 0xFF);
  for (size_t i = 0; i < n; ++i) EXPECT_EQ(p[i], static_cast<char>(i & 0xFF));
}

// Normal operation: two allocations yield distinct, non-overlapping regions.
TEST_F(ArenaTest_85, AllocateReturnsDistinctPointers_85) {
  const size_t n1 = 64;
  const size_t n2 = 128;
  char* p1 = arena_.Allocate(n1);
  char* p2 = arena_.Allocate(n2);

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_TRUE(RangesDoNotOverlap(p1, n1, p2, n2));
}

// Boundary: small (1 byte) allocation works and is isolated.
TEST_F(ArenaTest_85, AllocateSingleByte_85) {
  char* p = arena_.Allocate(1);
  ASSERT_NE(p, nullptr);
  *p = 0x7F;
  EXPECT_EQ(*p, 0x7F);

  // Another small allocation should not overlap.
  char* q = arena_.Allocate(1);
  ASSERT_NE(q, nullptr);
  EXPECT_TRUE(RangesDoNotOverlap(p, 1, q, 1));
}

// Exceptional (observable via assert): bytes == 0 should trigger a debug-time death.
// This uses the death test macro that skips on unsupported platforms/configs.
TEST_F(ArenaTest_85, AllocateZeroBytesDeath_85) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH_IF_SUPPORTED({
    Arena a;
    (void)a.Allocate(0);
  }, "");
#endif
}

// External interaction via public API: MemoryUsage() is monotonic non-decreasing.
TEST_F(ArenaTest_85, MemoryUsageMonotonic_85) {
  size_t mu0 = arena_.MemoryUsage();
  char* p = arena_.Allocate(256);
  ASSERT_NE(p, nullptr);
  size_t mu1 = arena_.MemoryUsage();
  EXPECT_GE(mu1, mu0);

  (void)arena_.Allocate(4096);
  size_t mu2 = arena_.MemoryUsage();
  EXPECT_GE(mu2, mu1);
}

// Boundary/normal: aligned allocation returns a pointer aligned to at least pointer alignment.
TEST_F(ArenaTest_85, AllocateAlignedHasPointerAlignment_85) {
  const size_t req = 7; // arbitrary non-multiple to exercise alignment behavior
  char* p = arena_.AllocateAligned(req);
  ASSERT_NE(p, nullptr);

  constexpr size_t kMinAlign = alignof(void*);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p) % kMinAlign, 0u);

  // Memory is writable.
  for (size_t i = 0; i < req; ++i) p[i] = static_cast<char>(i);
  for (size_t i = 0; i < req; ++i) EXPECT_EQ(p[i], static_cast<char>(i));
}

// Stress/normal: many small allocations should all be valid and non-overlapping.
TEST_F(ArenaTest_85, ManySmallAllocationsNonOverlapping_85) {
  std::vector<std::pair<char*, size_t>> blocks;
  blocks.reserve(100);

  for (int i = 1; i <= 100; ++i) {
    size_t n = static_cast<size_t>(i % 13 + 1); // sizes 1..13
    char* p = arena_.Allocate(n);
    ASSERT_NE(p, nullptr);
    // Touch first and last byte to ensure writability.
    p[0] = static_cast<char>(i);
    p[n - 1] = static_cast<char>(i * 2);
    blocks.emplace_back(p, n);
  }

  // Verify no pair overlaps.
  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size(); ++j) {
      EXPECT_TRUE(RangesDoNotOverlap(blocks[i].first, blocks[i].second,
                                     blocks[j].first, blocks[j].second));
    }
  }
}

// Large allocation scenario: should succeed and be writable.
TEST_F(ArenaTest_85, LargeAllocationWritable_85) {
  const size_t n = 1 << 20; // 1 MiB
  char* p = arena_.Allocate(n);
  ASSERT_NE(p, nullptr);
  p[0] = 0x12;
  p[n - 1] = 0x34;
  EXPECT_EQ(p[0], 0x12);
  EXPECT_EQ(p[n - 1], 0x34);
}
