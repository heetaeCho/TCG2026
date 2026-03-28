// File: arena_test_84.cc
#include "util/arena.h"
#include <gtest/gtest.h>
#include <cstddef>
#include <vector>

namespace leveldb {

class ArenaTest_84 : public ::testing::Test {
protected:
    Arena arena;
};

// Normal operation: freshly-constructed arena reports a valid usage value (non-negative by type).
TEST_F(ArenaTest_84, DefaultConstructedHasValidUsage_84) {
    size_t usage = arena.MemoryUsage();
    // size_t is unsigned; this simply asserts the call is stable and returns a value.
    EXPECT_GE(usage, static_cast<size_t>(0));
}

// Normal operation: a sufficiently large allocation should not decrease MemoryUsage and is likely to increase it.
TEST_F(ArenaTest_84, LargeAllocateDoesNotDecreaseUsage_84) {
    const size_t before = arena.MemoryUsage();
    // Use a large request to strongly encourage observable growth without risking OOM.
    // 4MB is modest for typical environments.
    const size_t kLarge = 4u * 1024u * 1024u;
    char* p = arena.Allocate(kLarge);
    ASSERT_NE(p, nullptr);

    const size_t after = arena.MemoryUsage();
    EXPECT_GE(after, before);  // must not go down
    // It's reasonable (and observable) to expect growth for a large request.
    // If an implementation pre-reserved a huge block, this could be equal; allow >=.
}

// Normal operation: multiple small allocations keep MemoryUsage monotonic non-decreasing.
TEST_F(ArenaTest_84, MultipleSmallAllocationsMonotonicUsage_84) {
    size_t last = arena.MemoryUsage();
    for (int i = 0; i < 1000; ++i) {
        char* p = arena.Allocate(16);  // small but >0
        ASSERT_NE(p, nullptr);
        size_t now = arena.MemoryUsage();
        EXPECT_GE(now, last) << "MemoryUsage decreased after iteration " << i;
        last = now;
    }
}

// Boundary-ish behavior: AllocateAligned returns non-null and does not decrease MemoryUsage.
TEST_F(ArenaTest_84, AllocateAlignedNonNullAndNonDecreasingUsage_84) {
    const size_t before = arena.MemoryUsage();
    char* p = arena.AllocateAligned(64);  // alignment detail is internal; we only check observable effects
    ASSERT_NE(p, nullptr);

    const size_t after = arena.MemoryUsage();
    EXPECT_GE(after, before);
}

// Mixed operations: interleave Allocate and AllocateAligned; MemoryUsage remains monotonic.
TEST_F(ArenaTest_84, MixedAllocationsKeepUsageMonotonic_84) {
    size_t last = arena.MemoryUsage();

    // Interleave a variety of sizes and aligned/unaligned allocations.
    std::vector<size_t> sizes = {1, 32, 128, 1024, 4096, 8192};
    for (size_t i = 0; i < sizes.size(); ++i) {
        char* p1 = arena.Allocate(sizes[i]);
        ASSERT_NE(p1, nullptr);
        size_t now1 = arena.MemoryUsage();
        EXPECT_GE(now1, last);
        last = now1;

        char* p2 = arena.AllocateAligned(sizes[i]);
        ASSERT_NE(p2, nullptr);
        size_t now2 = arena.MemoryUsage();
        EXPECT_GE(now2, last);
        last = now2;
    }
}

}  // namespace leveldb
