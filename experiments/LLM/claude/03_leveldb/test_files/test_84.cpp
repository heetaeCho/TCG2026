#include "util/arena.h"
#include <gtest/gtest.h>
#include <cstring>
#include <vector>

namespace leveldb {

class ArenaTest_84 : public ::testing::Test {
 protected:
  Arena arena_;
};

TEST_F(ArenaTest_84, InitialMemoryUsageIsZero_84) {
  Arena arena;
  EXPECT_EQ(arena.MemoryUsage(), 0);
}

TEST_F(ArenaTest_84, AllocateReturnsNonNull_84) {
  char* ptr = arena_.Allocate(10);
  EXPECT_NE(ptr, nullptr);
}

TEST_F(ArenaTest_84, AllocateIncreasesMemoryUsage_84) {
  size_t before = arena_.MemoryUsage();
  arena_.Allocate(100);
  size_t after = arena_.MemoryUsage();
  EXPECT_GT(after, before);
}

TEST_F(ArenaTest_84, AllocateSmallAmounts_84) {
  char* p1 = arena_.Allocate(1);
  char* p2 = arena_.Allocate(1);
  EXPECT_NE(p1, nullptr);
  EXPECT_NE(p2, nullptr);
  EXPECT_NE(p1, p2);
}

TEST_F(ArenaTest_84, AllocateWriteAndRead_84) {
  const size_t size = 256;
  char* ptr = arena_.Allocate(size);
  ASSERT_NE(ptr, nullptr);
  // Write data
  for (size_t i = 0; i < size; i++) {
    ptr[i] = static_cast<char>(i & 0xFF);
  }
  // Read back and verify
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ptr[i], static_cast<char>(i & 0xFF));
  }
}

TEST_F(ArenaTest_84, AllocateLargeBlock_84) {
  // Allocate something larger than the default block size (typically 4096)
  const size_t large_size = 8192;
  char* ptr = arena_.Allocate(large_size);
  EXPECT_NE(ptr, nullptr);
  EXPECT_GT(arena_.MemoryUsage(), 0);
}

TEST_F(ArenaTest_84, AllocateMultipleLargeBlocks_84) {
  const size_t large_size = 10000;
  char* p1 = arena_.Allocate(large_size);
  size_t usage1 = arena_.MemoryUsage();
  char* p2 = arena_.Allocate(large_size);
  size_t usage2 = arena_.MemoryUsage();
  EXPECT_NE(p1, nullptr);
  EXPECT_NE(p2, nullptr);
  EXPECT_NE(p1, p2);
  EXPECT_GT(usage2, usage1);
}

TEST_F(ArenaTest_84, AllocateAlignedReturnsNonNull_84) {
  char* ptr = arena_.AllocateAligned(10);
  EXPECT_NE(ptr, nullptr);
}

TEST_F(ArenaTest_84, AllocateAlignedIsAligned_84) {
  for (int i = 0; i < 100; i++) {
    char* ptr = arena_.AllocateAligned(i + 1);
    ASSERT_NE(ptr, nullptr);
    // Should be aligned to pointer size (typically 8 bytes)
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    EXPECT_EQ(addr % sizeof(void*), 0)
        << "Allocation " << i << " not aligned: addr=" << addr;
  }
}

TEST_F(ArenaTest_84, AllocateAlignedIncreasesMemoryUsage_84) {
  size_t before = arena_.MemoryUsage();
  arena_.AllocateAligned(100);
  size_t after = arena_.MemoryUsage();
  EXPECT_GT(after, before);
}

TEST_F(ArenaTest_84, AllocateAlignedWriteAndRead_84) {
  const size_t size = 128;
  char* ptr = arena_.AllocateAligned(size);
  ASSERT_NE(ptr, nullptr);
  std::memset(ptr, 0xAB, size);
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(static_cast<unsigned char>(ptr[i]), 0xAB);
  }
}

TEST_F(ArenaTest_84, AllocateAlignedLargeBlock_84) {
  const size_t large_size = 16384;
  char* ptr = arena_.AllocateAligned(large_size);
  EXPECT_NE(ptr, nullptr);
  uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
  EXPECT_EQ(addr % sizeof(void*), 0);
}

TEST_F(ArenaTest_84, MixedAllocations_84) {
  std::vector<std::pair<char*, size_t>> allocations;
  for (int i = 0; i < 100; i++) {
    size_t size = (i * 37 + 1) % 1000 + 1;
    char* ptr;
    if (i % 2 == 0) {
      ptr = arena_.Allocate(size);
    } else {
      ptr = arena_.AllocateAligned(size);
    }
    ASSERT_NE(ptr, nullptr);
    allocations.push_back({ptr, size});
  }

  // Verify all allocations are distinct (non-overlapping)
  for (size_t i = 0; i < allocations.size(); i++) {
    for (size_t j = i + 1; j < allocations.size(); j++) {
      char* start_i = allocations[i].first;
      char* end_i = start_i + allocations[i].second;
      char* start_j = allocations[j].first;
      char* end_j = start_j + allocations[j].second;
      // No overlap: one ends before the other starts
      EXPECT_TRUE(end_i <= start_j || end_j <= start_i)
          << "Allocations " << i << " and " << j << " overlap";
    }
  }
}

TEST_F(ArenaTest_84, MemoryUsageMonotonicallyIncreases_84) {
  size_t prev = arena_.MemoryUsage();
  for (int i = 0; i < 50; i++) {
    arena_.Allocate(100);
    size_t current = arena_.MemoryUsage();
    EXPECT_GE(current, prev);
    prev = current;
  }
}

TEST_F(ArenaTest_84, AllocateOneByte_84) {
  char* ptr = arena_.Allocate(1);
  EXPECT_NE(ptr, nullptr);
  *ptr = 'x';
  EXPECT_EQ(*ptr, 'x');
}

TEST_F(ArenaTest_84, AllocateAlignedOneByte_84) {
  char* ptr = arena_.AllocateAligned(1);
  EXPECT_NE(ptr, nullptr);
  uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
  EXPECT_EQ(addr % sizeof(void*), 0);
  *ptr = 'y';
  EXPECT_EQ(*ptr, 'y');
}

TEST_F(ArenaTest_84, AllocateVeryLargeBlock_84) {
  // Allocate 1MB
  const size_t size = 1024 * 1024;
  char* ptr = arena_.Allocate(size);
  EXPECT_NE(ptr, nullptr);
  // Write to first and last byte
  ptr[0] = 'A';
  ptr[size - 1] = 'Z';
  EXPECT_EQ(ptr[0], 'A');
  EXPECT_EQ(ptr[size - 1], 'Z');
  EXPECT_GE(arena_.MemoryUsage(), size);
}

TEST_F(ArenaTest_84, MultipleArenasIndependent_84) {
  Arena arena1;
  Arena arena2;

  arena1.Allocate(1000);
  size_t usage1 = arena1.MemoryUsage();

  arena2.Allocate(500);
  size_t usage2 = arena2.MemoryUsage();

  // arena1's memory usage should not change after arena2 allocation
  EXPECT_EQ(arena1.MemoryUsage(), usage1);
  // Both should have independent usage
  EXPECT_GT(usage1, 0);
  EXPECT_GT(usage2, 0);
}

TEST_F(ArenaTest_84, AllocateManySmallAllocations_84) {
  const int num_allocations = 10000;
  size_t total_allocated = 0;
  for (int i = 0; i < num_allocations; i++) {
    char* ptr = arena_.Allocate(1);
    ASSERT_NE(ptr, nullptr);
    *ptr = static_cast<char>(i & 0xFF);
    total_allocated += 1;
  }
  // Memory usage should account for all allocations (plus overhead)
  EXPECT_GE(arena_.MemoryUsage(), total_allocated);
}

TEST_F(ArenaTest_84, AllocateAlignedVaryingSizes_84) {
  std::vector<size_t> sizes = {1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 32,
                                64, 128, 255, 256, 512, 1024, 2048, 4096};
  for (size_t size : sizes) {
    char* ptr = arena_.AllocateAligned(size);
    ASSERT_NE(ptr, nullptr) << "Failed for size=" << size;
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    EXPECT_EQ(addr % sizeof(void*), 0) << "Not aligned for size=" << size;
  }
}

TEST_F(ArenaTest_84, MemoryUsageAfterAlignedAllocations_84) {
  Arena arena;
  arena.AllocateAligned(1);
  size_t usage1 = arena.MemoryUsage();
  arena.AllocateAligned(5000);
  size_t usage2 = arena.MemoryUsage();
  EXPECT_GT(usage2, usage1);
}

}  // namespace leveldb
