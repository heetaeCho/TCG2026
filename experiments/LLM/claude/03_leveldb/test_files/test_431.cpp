#include "gtest/gtest.h"
#include "util/arena.h"

namespace leveldb {

// Test basic construction and destruction
TEST(ArenaTest_431, ConstructionAndDestruction_431) {
  Arena arena;
  // Should be constructible and destructible without issues
  EXPECT_EQ(arena.MemoryUsage(), 0);
}

// Test single small allocation
TEST(ArenaTest_431, SingleSmallAllocation_431) {
  Arena arena;
  char* ptr = arena.Allocate(10);
  ASSERT_NE(ptr, nullptr);
  // Should be able to write to the allocated memory
  for (int i = 0; i < 10; i++) {
    ptr[i] = static_cast<char>(i);
  }
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(ptr[i], static_cast<char>(i));
  }
}

// Test memory usage increases after allocation
TEST(ArenaTest_431, MemoryUsageIncreasesAfterAllocation_431) {
  Arena arena;
  size_t initial_usage = arena.MemoryUsage();
  arena.Allocate(100);
  EXPECT_GT(arena.MemoryUsage(), initial_usage);
}

// Test multiple allocations
TEST(ArenaTest_431, MultipleAllocations_431) {
  Arena arena;
  char* ptr1 = arena.Allocate(100);
  char* ptr2 = arena.Allocate(200);
  char* ptr3 = arena.Allocate(300);
  ASSERT_NE(ptr1, nullptr);
  ASSERT_NE(ptr2, nullptr);
  ASSERT_NE(ptr3, nullptr);
  // Pointers should be different
  EXPECT_NE(ptr1, ptr2);
  EXPECT_NE(ptr2, ptr3);
  EXPECT_NE(ptr1, ptr3);
}

// Test allocations don't overlap
TEST(ArenaTest_431, AllocationsDoNotOverlap_431) {
  Arena arena;
  char* ptr1 = arena.Allocate(100);
  char* ptr2 = arena.Allocate(100);
  // Fill first allocation
  memset(ptr1, 'A', 100);
  // Fill second allocation
  memset(ptr2, 'B', 100);
  // Verify first allocation is still intact
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(ptr1[i], 'A');
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(ptr2[i], 'B');
  }
}

// Test allocation of 1 byte (boundary)
TEST(ArenaTest_431, AllocateOneByte_431) {
  Arena arena;
  char* ptr = arena.Allocate(1);
  ASSERT_NE(ptr, nullptr);
  ptr[0] = 'X';
  EXPECT_EQ(ptr[0], 'X');
}

// Test large allocation that exceeds block size
TEST(ArenaTest_431, LargeAllocation_431) {
  Arena arena;
  // Allocate a large block (larger than typical block size of 4096)
  size_t large_size = 8192;
  char* ptr = arena.Allocate(large_size);
  ASSERT_NE(ptr, nullptr);
  // Write and verify
  memset(ptr, 'Z', large_size);
  for (size_t i = 0; i < large_size; i++) {
    EXPECT_EQ(ptr[i], 'Z');
  }
}

// Test very large allocation
TEST(ArenaTest_431, VeryLargeAllocation_431) {
  Arena arena;
  size_t very_large_size = 1024 * 1024;  // 1 MB
  char* ptr = arena.Allocate(very_large_size);
  ASSERT_NE(ptr, nullptr);
  ptr[0] = 'A';
  ptr[very_large_size - 1] = 'Z';
  EXPECT_EQ(ptr[0], 'A');
  EXPECT_EQ(ptr[very_large_size - 1], 'Z');
}

// Test AllocateAligned basic functionality
TEST(ArenaTest_431, AllocateAlignedBasic_431) {
  Arena arena;
  char* ptr = arena.AllocateAligned(100);
  ASSERT_NE(ptr, nullptr);
  // Check alignment (should be aligned to pointer size or 8 bytes)
  size_t align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) % align, 0);
}

// Test AllocateAligned with multiple allocations
TEST(ArenaTest_431, AllocateAlignedMultiple_431) {
  Arena arena;
  for (int i = 0; i < 100; i++) {
    char* ptr = arena.AllocateAligned(i + 1);
    ASSERT_NE(ptr, nullptr);
    size_t align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
    EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) % align, 0);
  }
}

// Test AllocateAligned with 1 byte
TEST(ArenaTest_431, AllocateAlignedOneByte_431) {
  Arena arena;
  char* ptr = arena.AllocateAligned(1);
  ASSERT_NE(ptr, nullptr);
  size_t align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) % align, 0);
  ptr[0] = 'T';
  EXPECT_EQ(ptr[0], 'T');
}

// Test AllocateAligned with large allocation
TEST(ArenaTest_431, AllocateAlignedLarge_431) {
  Arena arena;
  size_t large_size = 16384;
  char* ptr = arena.AllocateAligned(large_size);
  ASSERT_NE(ptr, nullptr);
  size_t align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) % align, 0);
  memset(ptr, 'Q', large_size);
  EXPECT_EQ(ptr[0], 'Q');
  EXPECT_EQ(ptr[large_size - 1], 'Q');
}

// Test mixing Allocate and AllocateAligned
TEST(ArenaTest_431, MixedAllocations_431) {
  Arena arena;
  char* ptr1 = arena.Allocate(50);
  char* ptr2 = arena.AllocateAligned(60);
  char* ptr3 = arena.Allocate(70);
  char* ptr4 = arena.AllocateAligned(80);
  ASSERT_NE(ptr1, nullptr);
  ASSERT_NE(ptr2, nullptr);
  ASSERT_NE(ptr3, nullptr);
  ASSERT_NE(ptr4, nullptr);
  // All should be distinct
  EXPECT_NE(ptr1, ptr2);
  EXPECT_NE(ptr1, ptr3);
  EXPECT_NE(ptr1, ptr4);
  EXPECT_NE(ptr2, ptr3);
  EXPECT_NE(ptr2, ptr4);
  EXPECT_NE(ptr3, ptr4);
}

// Test memory usage monotonically increases
TEST(ArenaTest_431, MemoryUsageMonotonicallyIncreases_431) {
  Arena arena;
  size_t prev_usage = arena.MemoryUsage();
  for (int i = 0; i < 50; i++) {
    arena.Allocate(100);
    size_t curr_usage = arena.MemoryUsage();
    EXPECT_GE(curr_usage, prev_usage);
    prev_usage = curr_usage;
  }
}

// Test many small allocations
TEST(ArenaTest_431, ManySmallAllocations_431) {
  Arena arena;
  const int num_allocs = 10000;
  std::vector<char*> ptrs;
  for (int i = 0; i < num_allocs; i++) {
    char* ptr = arena.Allocate(1);
    ASSERT_NE(ptr, nullptr);
    *ptr = static_cast<char>(i & 0xFF);
    ptrs.push_back(ptr);
  }
  // Verify all allocations are still valid
  for (int i = 0; i < num_allocs; i++) {
    EXPECT_EQ(*ptrs[i], static_cast<char>(i & 0xFF));
  }
}

// Test that memory usage is positive after allocation
TEST(ArenaTest_431, MemoryUsagePositiveAfterAllocation_431) {
  Arena arena;
  arena.Allocate(1);
  EXPECT_GT(arena.MemoryUsage(), 0u);
}

// Test allocations that force multiple block allocations
TEST(ArenaTest_431, MultipleBlockAllocations_431) {
  Arena arena;
  // Allocate enough to force multiple blocks (default block size is typically 4096)
  for (int i = 0; i < 100; i++) {
    char* ptr = arena.Allocate(500);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, static_cast<char>(i), 500);
  }
  EXPECT_GT(arena.MemoryUsage(), 0u);
}

// Test that copy constructor is deleted (compile-time check, but we document it)
TEST(ArenaTest_431, CopyAndAssignmentDeleted_431) {
  // These should not compile:
  // Arena a;
  // Arena b(a);        // copy constructor deleted
  // Arena c; c = a;    // assignment operator deleted
  // This test just verifies Arena can be used normally
  Arena arena;
  char* ptr = arena.Allocate(10);
  ASSERT_NE(ptr, nullptr);
}

// Test AllocateAligned after many unaligned allocations
TEST(ArenaTest_431, AllocateAlignedAfterUnaligned_431) {
  Arena arena;
  // Do some odd-sized allocations to potentially misalign the internal pointer
  arena.Allocate(3);
  arena.Allocate(7);
  arena.Allocate(13);
  
  char* aligned_ptr = arena.AllocateAligned(64);
  ASSERT_NE(aligned_ptr, nullptr);
  size_t align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  EXPECT_EQ(reinterpret_cast<uintptr_t>(aligned_ptr) % align, 0);
}

// Test sequential allocations with varying sizes
TEST(ArenaTest_431, VaryingSizeAllocations_431) {
  Arena arena;
  std::vector<std::pair<char*, size_t>> allocations;
  
  size_t sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
  for (size_t size : sizes) {
    char* ptr = arena.Allocate(size);
    ASSERT_NE(ptr, nullptr);
    memset(ptr, 0xAB, size);
    allocations.push_back({ptr, size});
  }
  
  // Verify all allocations
  for (auto& [ptr, size] : allocations) {
    for (size_t j = 0; j < size; j++) {
      EXPECT_EQ(static_cast<unsigned char>(ptr[j]), 0xAB);
    }
  }
}

}  // namespace leveldb
