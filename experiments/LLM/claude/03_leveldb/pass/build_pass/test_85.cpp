#include "util/arena.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstring>
#include <set>

namespace leveldb {

class ArenaTest_85 : public ::testing::Test {
 protected:
  Arena arena_;
};

// Test basic allocation returns a non-null pointer
TEST_F(ArenaTest_85, BasicAllocateReturnsNonNull_85) {
  char* ptr = arena_.Allocate(1);
  ASSERT_NE(ptr, nullptr);
}

// Test allocating a single byte
TEST_F(ArenaTest_85, AllocateSingleByte_85) {
  char* ptr = arena_.Allocate(1);
  ASSERT_NE(ptr, nullptr);
  // Should be writable
  *ptr = 'A';
  EXPECT_EQ(*ptr, 'A');
}

// Test that multiple allocations return different pointers
TEST_F(ArenaTest_85, MultipleAllocationsReturnDifferentPointers_85) {
  char* ptr1 = arena_.Allocate(10);
  char* ptr2 = arena_.Allocate(10);
  ASSERT_NE(ptr1, nullptr);
  ASSERT_NE(ptr2, nullptr);
  EXPECT_NE(ptr1, ptr2);
}

// Test that allocated memory is writable and readable
TEST_F(ArenaTest_85, AllocatedMemoryIsWritableAndReadable_85) {
  const size_t size = 100;
  char* ptr = arena_.Allocate(size);
  ASSERT_NE(ptr, nullptr);
  for (size_t i = 0; i < size; i++) {
    ptr[i] = static_cast<char>(i % 256);
  }
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(ptr[i], static_cast<char>(i % 256));
  }
}

// Test that small consecutive allocations don't overlap
TEST_F(ArenaTest_85, SmallConsecutiveAllocationsNoOverlap_85) {
  const int num_allocs = 100;
  const size_t alloc_size = 50;
  std::vector<char*> ptrs;
  
  for (int i = 0; i < num_allocs; i++) {
    ptrs.push_back(arena_.Allocate(alloc_size));
    ASSERT_NE(ptrs.back(), nullptr);
  }
  
  // Write distinct data to each allocation
  for (int i = 0; i < num_allocs; i++) {
    std::memset(ptrs[i], static_cast<char>(i), alloc_size);
  }
  
  // Verify data integrity (no overlaps)
  for (int i = 0; i < num_allocs; i++) {
    for (size_t j = 0; j < alloc_size; j++) {
      EXPECT_EQ(ptrs[i][j], static_cast<char>(i));
    }
  }
}

// Test large allocation
TEST_F(ArenaTest_85, LargeAllocation_85) {
  const size_t large_size = 1024 * 1024;  // 1 MB
  char* ptr = arena_.Allocate(large_size);
  ASSERT_NE(ptr, nullptr);
  // Write to first and last byte to verify accessibility
  ptr[0] = 'X';
  ptr[large_size - 1] = 'Y';
  EXPECT_EQ(ptr[0], 'X');
  EXPECT_EQ(ptr[large_size - 1], 'Y');
}

// Test MemoryUsage increases after allocation
TEST_F(ArenaTest_85, MemoryUsageIncreasesAfterAllocation_85) {
  size_t initial_usage = arena_.MemoryUsage();
  arena_.Allocate(1000);
  size_t after_usage = arena_.MemoryUsage();
  EXPECT_GT(after_usage, initial_usage);
}

// Test MemoryUsage is initially zero or very small
TEST_F(ArenaTest_85, InitialMemoryUsage_85) {
  Arena fresh_arena;
  EXPECT_EQ(fresh_arena.MemoryUsage(), 0u);
}

// Test MemoryUsage keeps growing with more allocations
TEST_F(ArenaTest_85, MemoryUsageGrowsMonotonically_85) {
  size_t prev_usage = arena_.MemoryUsage();
  for (int i = 0; i < 10; i++) {
    arena_.Allocate(5000);
    size_t current_usage = arena_.MemoryUsage();
    EXPECT_GE(current_usage, prev_usage);
    prev_usage = current_usage;
  }
}

// Test AllocateAligned returns non-null
TEST_F(ArenaTest_85, AllocateAlignedReturnsNonNull_85) {
  char* ptr = arena_.AllocateAligned(100);
  ASSERT_NE(ptr, nullptr);
}

// Test AllocateAligned returns properly aligned pointer
TEST_F(ArenaTest_85, AllocateAlignedIsAligned_85) {
  for (int i = 0; i < 50; i++) {
    char* ptr = arena_.AllocateAligned(1 + i * 7);
    ASSERT_NE(ptr, nullptr);
    // Should be aligned to at least sizeof(void*)
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    EXPECT_EQ(addr % sizeof(void*), 0u)
        << "Pointer not aligned at iteration " << i;
  }
}

// Test AllocateAligned for single byte
TEST_F(ArenaTest_85, AllocateAlignedSingleByte_85) {
  char* ptr = arena_.AllocateAligned(1);
  ASSERT_NE(ptr, nullptr);
  uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
  EXPECT_EQ(addr % sizeof(void*), 0u);
  *ptr = 'Z';
  EXPECT_EQ(*ptr, 'Z');
}

// Test mixing Allocate and AllocateAligned
TEST_F(ArenaTest_85, MixedAllocateAndAllocateAligned_85) {
  std::vector<std::pair<char*, size_t>> allocs;
  
  for (int i = 0; i < 50; i++) {
    size_t size = 1 + (i * 13) % 500;
    char* ptr;
    if (i % 2 == 0) {
      ptr = arena_.Allocate(size);
    } else {
      ptr = arena_.AllocateAligned(size);
    }
    ASSERT_NE(ptr, nullptr);
    allocs.push_back({ptr, size});
    std::memset(ptr, static_cast<char>(i), size);
  }
  
  // Verify all data is intact
  for (int i = 0; i < 50; i++) {
    for (size_t j = 0; j < allocs[i].second; j++) {
      EXPECT_EQ(allocs[i].first[j], static_cast<char>(i))
          << "Data corruption at allocation " << i << " offset " << j;
    }
  }
}

// Test many small allocations
TEST_F(ArenaTest_85, ManySmallAllocations_85) {
  const int count = 10000;
  std::set<char*> ptrs;
  for (int i = 0; i < count; i++) {
    char* ptr = arena_.Allocate(1);
    ASSERT_NE(ptr, nullptr);
    // All pointers should be unique
    EXPECT_TRUE(ptrs.insert(ptr).second) << "Duplicate pointer at iteration " << i;
  }
}

// Test allocation of varying sizes
TEST_F(ArenaTest_85, VaryingSizeAllocations_85) {
  std::vector<size_t> sizes = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 
                                1024, 2048, 4096, 8192, 16384};
  for (size_t sz : sizes) {
    char* ptr = arena_.Allocate(sz);
    ASSERT_NE(ptr, nullptr) << "Failed to allocate " << sz << " bytes";
    // Verify writable
    ptr[0] = 'A';
    ptr[sz - 1] = 'B';
    EXPECT_EQ(ptr[0], 'A');
    EXPECT_EQ(ptr[sz - 1], 'B');
  }
}

// Test large allocation followed by small allocation
TEST_F(ArenaTest_85, LargeFollowedBySmallAllocation_85) {
  char* large = arena_.Allocate(100000);
  ASSERT_NE(large, nullptr);
  char* small = arena_.Allocate(10);
  ASSERT_NE(small, nullptr);
  EXPECT_NE(large, small);
  
  // Both should be independently writable
  std::memset(large, 'L', 100000);
  std::memset(small, 'S', 10);
  
  EXPECT_EQ(large[0], 'L');
  EXPECT_EQ(large[99999], 'L');
  EXPECT_EQ(small[0], 'S');
  EXPECT_EQ(small[9], 'S');
}

// Test that MemoryUsage accounts for large allocations
TEST_F(ArenaTest_85, MemoryUsageAccountsForLargeAllocs_85) {
  size_t before = arena_.MemoryUsage();
  arena_.Allocate(1024 * 1024);  // 1 MB
  size_t after = arena_.MemoryUsage();
  // Memory usage should increase by at least the allocation size
  EXPECT_GE(after - before, 1024u * 1024u);
}

// Test AllocateAligned with large allocation
TEST_F(ArenaTest_85, AllocateAlignedLargeAllocation_85) {
  const size_t large_size = 100000;
  char* ptr = arena_.AllocateAligned(large_size);
  ASSERT_NE(ptr, nullptr);
  uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
  EXPECT_EQ(addr % sizeof(void*), 0u);
  ptr[0] = 'X';
  ptr[large_size - 1] = 'Y';
  EXPECT_EQ(ptr[0], 'X');
  EXPECT_EQ(ptr[large_size - 1], 'Y');
}

// Test that a new Arena starts with zero memory usage
TEST_F(ArenaTest_85, NewArenaZeroMemoryUsage_85) {
  Arena a;
  EXPECT_EQ(a.MemoryUsage(), 0u);
}

// Test allocations that are exactly at block size boundary (typically 4096)
TEST_F(ArenaTest_85, AllocationAtBlockSizeBoundary_85) {
  // The internal block size is typically 4096, so test around that
  char* ptr1 = arena_.Allocate(4096);
  ASSERT_NE(ptr1, nullptr);
  char* ptr2 = arena_.Allocate(4096);
  ASSERT_NE(ptr2, nullptr);
  EXPECT_NE(ptr1, ptr2);
}

// Test very large allocation
TEST_F(ArenaTest_85, VeryLargeAllocation_85) {
  const size_t very_large = 10 * 1024 * 1024;  // 10 MB
  char* ptr = arena_.Allocate(very_large);
  ASSERT_NE(ptr, nullptr);
  ptr[0] = 'A';
  ptr[very_large - 1] = 'Z';
  EXPECT_EQ(ptr[0], 'A');
  EXPECT_EQ(ptr[very_large - 1], 'Z');
}

// Test that allocations within the same block are contiguous (small sequential allocations)
TEST_F(ArenaTest_85, SmallSequentialAllocationsFromSameBlock_85) {
  // First allocation triggers a new block
  char* ptr1 = arena_.Allocate(10);
  char* ptr2 = arena_.Allocate(20);
  ASSERT_NE(ptr1, nullptr);
  ASSERT_NE(ptr2, nullptr);
  // ptr2 should come after ptr1 in the same block
  // (ptr1 + 10 == ptr2 if they're in the same block)
  // This tests the fast path of Allocate
  EXPECT_EQ(ptr1 + 10, ptr2);
}

}  // namespace leveldb
