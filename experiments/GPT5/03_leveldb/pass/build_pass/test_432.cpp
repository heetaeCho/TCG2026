// File: arena_allocate_aligned_test.cc
#include "util/arena.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace {

inline size_t RequiredAlign() {
  // Must match the contract used by AllocateAligned:
  // alignment is max(sizeof(void*), 8) and a power of two.
  return std::max(sizeof(void*), static_cast<size_t>(8));
}

class ArenaAllocateAlignedTest_432 : public ::testing::Test {
protected:
  leveldb::Arena arena_;
};

TEST_F(ArenaAllocateAlignedTest_432, ReturnsAlignedPointerForVariousSizes_432) {
  const size_t kAlign = RequiredAlign();

  // Try a range of sizes, including odd and non-power-of-two sizes.
  std::vector<size_t> sizes = {1, 2, 3, 7, 8, 9, 15, 16, 31, 32, 63, 64, 127, 128, 257, 4095, 4096};

  for (size_t sz : sizes) {
    char* p = arena_.AllocateAligned(sz);
    ASSERT_NE(p, nullptr);
    uintptr_t addr = reinterpret_cast<uintptr_t>(p);
    EXPECT_EQ(addr & (kAlign - 1), 0u) << "Size=" << sz << " addr=" << addr;
  }
}

TEST_F(ArenaAllocateAlignedTest_432, ConsecutiveAlignedAllocationsDoNotOverlap_432) {
  const size_t a = 13;
  const size_t b = 29;

  char* p1 = arena_.AllocateAligned(a);
  ASSERT_NE(p1, nullptr);

  char* p2 = arena_.AllocateAligned(b);
  ASSERT_NE(p2, nullptr);

  // Pointers must be distinct and second allocation must not overlap the first.
  EXPECT_NE(p1, p2);
  EXPECT_GE(p2, p1 + a);
}

TEST_F(ArenaAllocateAlignedTest_432, MemoryUsageDoesNotDecreaseAndReflectsGrowth_432) {
  const size_t before = arena_.MemoryUsage();

  // Perform multiple allocations (including larger ones) to grow usage.
  (void)arena_.AllocateAligned(64);
  (void)arena_.AllocateAligned(1024);
  (void)arena_.AllocateAligned(777);

  const size_t after = arena_.MemoryUsage();
  EXPECT_GE(after, before);
}

TEST_F(ArenaAllocateAlignedTest_432, LargeAllocationIsAligned_432) {
  // A large request should still return an aligned pointer.
  const size_t kAlign = RequiredAlign();
  const size_t large = 1 << 20; // 1 MiB (large enough to likely require a new block)
  char* p = arena_.AllocateAligned(large);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p) & (kAlign - 1), 0u);
}

TEST_F(ArenaAllocateAlignedTest_432, MixedAllocateThenAllocateAligned_AlignmentPreserved_432) {
  const size_t kAlign = RequiredAlign();

  // First do an unaligned Allocate (no alignment guarantee by interface).
  char* u = arena_.Allocate(3);
  ASSERT_NE(u, nullptr);

  // Now request an aligned allocation and verify alignment + no overlap.
  char* p = arena_.AllocateAligned(5);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p) & (kAlign - 1), 0u);
  EXPECT_GE(p, u + 3);
}

TEST_F(ArenaAllocateAlignedTest_432, ManySmallAlignedAllocations_AllAlignedAndDistinct_432) {
  const size_t kAlign = RequiredAlign();
  constexpr int kN = 1000;

  char* prev = nullptr;
  for (int i = 0; i < kN; ++i) {
    char* p = arena_.AllocateAligned(1);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p) & (kAlign - 1), 0u) << "i=" << i;
    if (prev) {
      EXPECT_NE(p, prev) << "Each call should yield a distinct region (i=" << i << ")";
    }
    prev = p;
  }
}

// Optional boundary case: size 0. We only check the call succeeds and alignment holds.
// We do NOT assert on (non-)consumption or pointer equality with subsequent calls,
// since those are internal behaviors.
TEST_F(ArenaAllocateAlignedTest_432, ZeroSizeStillReturnsAlignedPointer_432) {
  const size_t kAlign = RequiredAlign();
  char* p = arena_.AllocateAligned(0);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p) & (kAlign - 1), 0u);
}

}  // namespace
