#include "gtest/gtest.h"
#include "util/arena.h"

namespace leveldb {

// Test fixture for Arena tests
class ArenaTest_432 : public ::testing::Test {
 protected:
  Arena arena_;
};

// Basic allocation test - allocate a small amount of memory
TEST_F(ArenaTest_432, BasicAllocate_432) {
  char* ptr = arena_.Allocate(10);
  ASSERT_NE(ptr, nullptr);
  // Verify we can write to the allocated memory
  for (int i = 0; i < 10; i++) {
    ptr[i] = static_cast<char>(i);
  }
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(ptr[i], static_cast<char>(i));
  }
}

// Test AllocateAligned returns properly aligned memory
TEST_F(ArenaTest_432, AllocateAlignedReturnsAlignedPointer_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  for (int i = 1; i <= 128; i++) {
    char* ptr = arena_.AllocateAligned(i);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u)
        << "Allocation of size " << i << " not aligned to " << align;
  }
}

// Test multiple small allocations
TEST_F(ArenaTest_432, MultipleSmallAllocations_432) {
  std::vector<char*> ptrs;
  for (int i = 0; i < 100; i++) {
    char* ptr = arena_.Allocate(16);
    ASSERT_NE(ptr, nullptr);
    ptrs.push_back(ptr);
  }
  // Verify all pointers are distinct
  for (size_t i = 0; i < ptrs.size(); i++) {
    for (size_t j = i + 1; j < ptrs.size(); j++) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}

// Test allocation of a single byte
TEST_F(ArenaTest_432, AllocateSingleByte_432) {
  char* ptr = arena_.Allocate(1);
  ASSERT_NE(ptr, nullptr);
  ptr[0] = 'a';
  EXPECT_EQ(ptr[0], 'a');
}

// Test AllocateAligned with single byte
TEST_F(ArenaTest_432, AllocateAlignedSingleByte_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  char* ptr = arena_.AllocateAligned(1);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u);
  ptr[0] = 'x';
  EXPECT_EQ(ptr[0], 'x');
}

// Test large allocation
TEST_F(ArenaTest_432, LargeAllocation_432) {
  size_t large_size = 100000;
  char* ptr = arena_.Allocate(large_size);
  ASSERT_NE(ptr, nullptr);
  // Write to all allocated bytes to verify memory is accessible
  memset(ptr, 0xAB, large_size);
  for (size_t i = 0; i < large_size; i++) {
    EXPECT_EQ(static_cast<unsigned char>(ptr[i]), 0xAB);
  }
}

// Test large aligned allocation
TEST_F(ArenaTest_432, LargeAlignedAllocation_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  size_t large_size = 100000;
  char* ptr = arena_.AllocateAligned(large_size);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u);
  memset(ptr, 0xCD, large_size);
  for (size_t i = 0; i < large_size; i++) {
    EXPECT_EQ(static_cast<unsigned char>(ptr[i]), 0xCD);
  }
}

// Test MemoryUsage increases with allocations
TEST_F(ArenaTest_432, MemoryUsageIncreasesWithAllocations_432) {
  size_t initial_usage = arena_.MemoryUsage();
  arena_.Allocate(1000);
  size_t usage_after_first = arena_.MemoryUsage();
  EXPECT_GT(usage_after_first, initial_usage);

  arena_.Allocate(1000);
  size_t usage_after_second = arena_.MemoryUsage();
  EXPECT_GE(usage_after_second, usage_after_first);
}

// Test MemoryUsage with aligned allocations
TEST_F(ArenaTest_432, MemoryUsageWithAlignedAllocations_432) {
  size_t initial_usage = arena_.MemoryUsage();
  arena_.AllocateAligned(1000);
  size_t usage_after = arena_.MemoryUsage();
  EXPECT_GT(usage_after, initial_usage);
}

// Test mixed allocations (aligned and unaligned)
TEST_F(ArenaTest_432, MixedAllocations_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  
  char* p1 = arena_.Allocate(10);
  ASSERT_NE(p1, nullptr);
  
  char* p2 = arena_.AllocateAligned(20);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p2) & (align - 1), 0u);
  
  char* p3 = arena_.Allocate(30);
  ASSERT_NE(p3, nullptr);
  
  char* p4 = arena_.AllocateAligned(40);
  ASSERT_NE(p4, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(p4) & (align - 1), 0u);
  
  // Verify all are distinct
  EXPECT_NE(p1, p2);
  EXPECT_NE(p1, p3);
  EXPECT_NE(p1, p4);
  EXPECT_NE(p2, p3);
  EXPECT_NE(p2, p4);
  EXPECT_NE(p3, p4);
}

// Test that allocated memory doesn't overlap
TEST_F(ArenaTest_432, AllocationsDoNotOverlap_432) {
  char* p1 = arena_.Allocate(100);
  char* p2 = arena_.Allocate(100);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  
  memset(p1, 'A', 100);
  memset(p2, 'B', 100);
  
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(p1[i], 'A');
    EXPECT_EQ(p2[i], 'B');
  }
}

// Test aligned allocations don't overlap
TEST_F(ArenaTest_432, AlignedAllocationsDoNotOverlap_432) {
  char* p1 = arena_.AllocateAligned(100);
  char* p2 = arena_.AllocateAligned(100);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  
  memset(p1, 'X', 100);
  memset(p2, 'Y', 100);
  
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(p1[i], 'X');
    EXPECT_EQ(p2[i], 'Y');
  }
}

// Test many allocations to trigger multiple block allocations
TEST_F(ArenaTest_432, ManyAllocationsMultipleBlocks_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  // Each block is typically 4096 bytes, so allocate enough to span many blocks
  for (int i = 0; i < 1000; i++) {
    char* ptr = arena_.AllocateAligned(128);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u);
    memset(ptr, static_cast<char>(i & 0xFF), 128);
  }
  EXPECT_GT(arena_.MemoryUsage(), 0u);
}

// Test varying sizes of aligned allocations
TEST_F(ArenaTest_432, VaryingSizeAlignedAllocations_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  size_t sizes[] = {1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 32, 33, 
                    63, 64, 65, 127, 128, 255, 256, 512, 1024, 2048, 4096};
  for (size_t sz : sizes) {
    char* ptr = arena_.AllocateAligned(sz);
    ASSERT_NE(ptr, nullptr) << "Failed for size " << sz;
    EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u)
        << "Misaligned for size " << sz;
  }
}

// Test initial memory usage
TEST_F(ArenaTest_432, InitialMemoryUsage_432) {
  EXPECT_EQ(arena_.MemoryUsage(), 0u);
}

// Test allocation larger than typical block size
TEST_F(ArenaTest_432, AllocationLargerThanBlockSize_432) {
  // Typical block size is 4096, allocate much larger
  char* ptr = arena_.Allocate(1024 * 1024);
  ASSERT_NE(ptr, nullptr);
  memset(ptr, 0, 1024 * 1024);
}

// Test AllocateAligned larger than typical block size
TEST_F(ArenaTest_432, AllocateAlignedLargerThanBlockSize_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  char* ptr = arena_.AllocateAligned(1024 * 1024);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u);
  memset(ptr, 0xFF, 1024 * 1024);
}

// Test sequential aligned allocations maintain alignment
TEST_F(ArenaTest_432, SequentialAlignedAllocationsAfterOddSizeUnaligned_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  
  // Allocate an odd number of bytes (unaligned) to potentially misalign the pointer
  arena_.Allocate(3);
  
  // Now aligned allocation should still be properly aligned
  char* ptr = arena_.AllocateAligned(16);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) & (align - 1), 0u);
}

// Test multiple aligned allocations after odd-sized regular allocations
TEST_F(ArenaTest_432, AlignmentAfterVariousUnalignedAllocations_432) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  
  for (int odd_size = 1; odd_size <= 15; odd_size += 2) {
    arena_.Allocate(odd_size);
    char* aligned = arena_.AllocateAligned(16);
    ASSERT_NE(aligned, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(aligned) & (align - 1), 0u)
        << "Misaligned after allocating " << odd_size << " unaligned bytes";
  }
}

// Test that MemoryUsage is at least as large as what we allocated
TEST_F(ArenaTest_432, MemoryUsageAtLeastAsLargeAsAllocated_432) {
  size_t total_allocated = 0;
  for (int i = 0; i < 10; i++) {
    size_t sz = 1000;
    arena_.Allocate(sz);
    total_allocated += sz;
  }
  EXPECT_GE(arena_.MemoryUsage(), total_allocated);
}

}  // namespace leveldb
