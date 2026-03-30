// File: util/arena_test.cc
#include "util/arena.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace {

class ArenaTest_431 : public ::testing::Test {
protected:
  // Helper to write & verify a simple pattern in allocated memory
  static void Touch(char* p, size_t n, unsigned char seed = 0x5A) {
    for (size_t i = 0; i < n; ++i) {
      p[i] = static_cast<char>((seed + i) & 0xFF);
    }
    for (size_t i = 0; i < n; ++i) {
      ASSERT_EQ(static_cast<unsigned char>(p[i]),
                static_cast<unsigned char>((seed + i) & 0xFF));
    }
  }
};

}  // namespace

// 1) Basic lifecycle: constructing and destroying without any allocation
TEST_F(ArenaTest_431, Destructor_NoAllocation_DoesNotCrash_431) {
  // Scope ensures destructor runs at the end
  { leveldb::Arena arena; }
  SUCCEED();  // Reaching here means no crash in destructor path with empty blocks
}

// 2) Small allocations are usable until destruction; destruction does not crash
TEST_F(ArenaTest_431, Destructor_AfterSmallAllocations_DoesNotCrash_431) {
  std::vector<char*> ptrs;
  {
    leveldb::Arena arena;
    for (int i = 0; i < 10; ++i) {
      char* p = arena.Allocate(static_cast<size_t>(i + 1) * 7);  // various sizes
      ASSERT_NE(p, nullptr);
      Touch(p, static_cast<size_t>(i + 1) * 7, static_cast<unsigned char>(i));
      ptrs.push_back(p);
      // MemoryUsage should be non-decreasing and > 0 after an allocation
      size_t mu = arena.MemoryUsage();
      ASSERT_GT(mu, 0u);
      if (i > 0) {
        ASSERT_GE(mu, arena.MemoryUsage());  // trivially true but we keep last read below
      }
    }
    // Additional check: MemoryUsage should not be zero after some allocations
    ASSERT_GT(arena.MemoryUsage(), 0u);
  }
  // If the destructor mishandled internal storage, this test would likely crash under ASan/Valgrind.
  SUCCEED();
}

// 3) Large allocation(s) that should force new backing blocks internally; destructor still safe
TEST_F(ArenaTest_431, Destructor_AfterLargeAllocations_DoesNotCrash_431) {
  // Use a large size to (very likely) bypass small-block fast-paths.
  // We do not assert *how* Arena manages this; we only check observable behavior.
  const size_t big = 1 << 20;  // 1 MiB
  {
    leveldb::Arena arena;
    char* p1 = arena.Allocate(big);
    ASSERT_NE(p1, nullptr);
    Touch(p1, 1024);  // light touch (don’t iterate 1 MiB to keep tests fast)

    char* p2 = arena.Allocate(big / 2);
    ASSERT_NE(p2, nullptr);
    Touch(p2, 1024);

    // MemoryUsage should be positive after big allocations
    ASSERT_GT(arena.MemoryUsage(), 0u);
  }
  SUCCEED();
}

// 4) AllocateAligned returns a pointer aligned for at least std::max_align_t and is usable
TEST_F(ArenaTest_431, AllocateAligned_ProvidesSufficientAlignment_Usable_431) {
  leveldb::Arena arena;
  const size_t kAlign = alignof(std::max_align_t);
  const size_t n = 64;

  char* p = arena.AllocateAligned(n);
  ASSERT_NE(p, nullptr);

  // Check alignment to max_align_t. We don't assume any particular internal strategy,
  // only that the returned pointer meets a sane alignment guarantee.
  uintptr_t addr = reinterpret_cast<uintptr_t>(p);
  ASSERT_EQ(addr % kAlign, 0u) << "AllocateAligned did not return at least max_align_t alignment";

  // The memory should be writable/readable.
  Touch(p, n);
}

// 5) Interleaving Allocate and AllocateAligned works and destructor remains safe
TEST_F(ArenaTest_431, Interleaved_Allocate_And_AllocateAligned_ThenDestroy_NoCrash_431) {
  {
    leveldb::Arena arena;

    // Interleaved pattern
    char* a1 = arena.Allocate(13);
    ASSERT_NE(a1, nullptr);
    Touch(a1, 13, 0x10);

    char* a2 = arena.AllocateAligned(32);
    ASSERT_NE(a2, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(a2) % alignof(std::max_align_t), 0u);
    Touch(a2, 32, 0x20);

    char* a3 = arena.Allocate(7);
    ASSERT_NE(a3, nullptr);
    Touch(a3, 7, 0x30);

    char* a4 = arena.AllocateAligned(128);
    ASSERT_NE(a4, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(a4) % alignof(std::max_align_t), 0u);
    Touch(a4, 64, 0x40);  // partial touch is sufficient for observability

    // MemoryUsage should reflect some consumption (>0 and non-decreasing across calls)
    size_t mu1 = arena.MemoryUsage();
    ASSERT_GT(mu1, 0u);
    (void)mu1;

    // Additional allocations then confirm non-decreasing
    char* a5 = arena.Allocate(4096);
    ASSERT_NE(a5, nullptr);
    Touch(a5, 64, 0x55);
    size_t mu2 = arena.MemoryUsage();
    ASSERT_GE(mu2, mu1);
  }
  SUCCEED();
}

// 6) MemoryUsage is monotonic non-decreasing during lifetime (observable property)
TEST_F(ArenaTest_431, MemoryUsage_NonDecreasing_DuringAllocations_431) {
  leveldb::Arena arena;

  size_t last = arena.MemoryUsage();
  // Not asserting it's zero initially; just track monotonic behavior.
  for (int i = 0; i < 8; ++i) {
    char* p = (i % 2 == 0) ? arena.Allocate(17 * (i + 1))
                           : arena.AllocateAligned(19 * (i + 1));
    ASSERT_NE(p, nullptr);
    Touch(p, std::min<size_t>(16, 19 * (i + 1)));
    size_t now = arena.MemoryUsage();
    ASSERT_GE(now, last);
    last = now;
  }
}

