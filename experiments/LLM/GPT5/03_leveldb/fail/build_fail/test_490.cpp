// File: table/iterator_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>
#include <vector>
#include <algorithm>

#include "leveldb/iterator.h"

using ::testing::UnorderedElementsAre;

namespace {

// Simple record type to observe cleanup invocations without peeking into Iterator internals.
struct Call {
  void* arg1;
  void* arg2;
};

// Global-ish sink for verifying observable side-effects of registered cleanups.
// (Kept inside anonymous namespace to avoid ODR issues across tests.)
static std::vector<Call> g_calls;

// A cleanup function matching the expected signature (two void* args).
// We don't assume anything else about Iterator internals.
static void RecordCleanup(void* a1, void* a2) {
  g_calls.push_back({a1, a2});
}

}  // namespace

namespace leveldb {

// Test fixture to keep tests tidy and reset shared state.
class IteratorTest_490 : public ::testing::Test {
 protected:
  void SetUp() override { g_calls.clear(); }
  void TearDown() override { g_calls.clear(); }
};

// 1) Basic construction/destruction smoke test: creating and destroying should not crash.
//    No cleanup functions are registered, so we simply verify "no calls" as the observable effect.
TEST_F(IteratorTest_490, ConstructAndDestroy_NoRegisteredCleanups_NoCalls_490) {
  {
    Iterator it;  // Constructor should succeed.
    // No further actions; we avoid calling any virtuals since behavior is unspecified.
  }  // Destructor runs here.
  EXPECT_TRUE(g_calls.empty());
}

// 2) RegisterCleanup should invoke the function on destruction with the same arguments.
TEST_F(IteratorTest_490, RegisterCleanup_InvokedOnDestruction_WithArgs_490) {
  void* a1 = reinterpret_cast<void*>(0x1);
  void* a2 = reinterpret_cast<void*>(0x2);

  {
    Iterator it;
    it.RegisterCleanup(&RecordCleanup, a1, a2);
  }  // Destructor should trigger the registered cleanup.

  ASSERT_EQ(g_calls.size(), 1u);
  EXPECT_EQ(g_calls[0].arg1, a1);
  EXPECT_EQ(g_calls[0].arg2, a2);
}

// 3) Multiple registrations: all cleanup callbacks should be invoked.
//    We do NOT assert ordering (black-box); we only assert that all expected pairs appear.
TEST_F(IteratorTest_490, MultipleRegisterCleanup_AllInvoked_OrderAgnostic_490) {
  void* a1 = reinterpret_cast<void*>(0x10);
  void* a2 = reinterpret_cast<void*>(0x20);
  void* b1 = reinterpret_cast<void*>(0x30);
  void* b2 = reinterpret_cast<void*>(0x40);

  {
    Iterator it;
    it.RegisterCleanup(&RecordCleanup, a1, a2);
    it.RegisterCleanup(&RecordCleanup, b1, b2);
  }  // Destructor should invoke both callbacks.

  ASSERT_EQ(g_calls.size(), 2u);

  // Order-agnostic verification.
  // Build a vector of (arg1,arg2) pairs to compare as a set.
  std::vector<std::pair<void*, void*>> seen = {
      {g_calls[0].arg1, g_calls[0].arg2},
      {g_calls[1].arg1, g_calls[1].arg2},
  };
  std::vector<std::pair<void*, void*>> expected = {{a1, a2}, {b1, b2}};

  // Sort by pointer value for stable comparison without assuming call order.
  auto by_ptrs = [](const std::pair<void*, void*>& lhs,
                    const std::pair<void*, void*>& rhs) {
    if (lhs.first != rhs.first) return lhs.first < rhs.first;
    return lhs.second < rhs.second;
  };
  std::sort(seen.begin(), seen.end(), by_ptrs);
  std::sort(expected.begin(), expected.end(), by_ptrs);
  EXPECT_EQ(seen, expected);
}

// 4) Registering a nullptr function should not cause a crash;
//    any valid registered cleanup should still be called. We only assert observable effects.
//    (We do NOT require Iterator to call or skip nullptr — we only require "no crash".)
TEST_F(IteratorTest_490, RegisterCleanup_NullFunction_DoesNotCrash_ValidStillRuns_490) {
  void* a1 = reinterpret_cast<void*>(0xAA);
  void* a2 = reinterpret_cast<void*>(0xBB);

  {
    Iterator it;
    // Intentionally pass nullptr for the function pointer. This must not crash.
    it.RegisterCleanup(nullptr, reinterpret_cast<void*>(0xDEAD), reinterpret_cast<void*>(0xBEEF));
    // Also register a valid one so we have an observable effect to check.
    it.RegisterCleanup(&RecordCleanup, a1, a2);
  }  // Destructor runs callbacks.

  // At minimum, the valid one must have been invoked exactly once.
  // If Iterator ignores nullptr, total calls == 1. If it tries to call it safely, still must not crash.
  ASSERT_FALSE(g_calls.empty());
  // Count occurrences of the valid pair.
  size_t count_valid = 0;
  for (const auto& c : g_calls) {
    if (c.arg1 == a1 && c.arg2 == a2) ++count_valid;
  }
  EXPECT_EQ(count_valid, 1u);
}

// 5) Copy/assignment should be deleted (non-copyable), per public interface.
TEST_F(IteratorTest_490, CopyAndAssignmentAreDeleted_490) {
  static_assert(!std::is_copy_constructible<Iterator>::value,
                "Iterator must not be copy-constructible");
  static_assert(!std::is_copy_assignable<Iterator>::value,
                "Iterator must not be copy-assignable");
}

}  // namespace leveldb
