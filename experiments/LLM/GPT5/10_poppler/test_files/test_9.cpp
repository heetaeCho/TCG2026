// TEST_ID is 9
// Unit tests for gmalloc() in ./TestProjects/poppler/goo/gmem.h

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

// Include the header under test
#include "TestProjects/poppler/goo/gmem.h"

namespace {

// Helper to find a very large allocation size that is likely to fail without
// depending on platform-specific behavior too much.
static size_t HugeSizeLikelyToFail() {
  // Use the largest size_t value. Most platforms will fail malloc for this.
  return std::numeric_limits<size_t>::max();
}

}  // namespace

// ---------- Normal operation ----------

TEST(GMallocTest_9, NonZeroSizeReturnsNonNull_9) {
  void* p = gmalloc(1);
  ASSERT_NE(p, nullptr);
  std::free(p);
}

TEST(GMallocTest_9, ReasonableSizeCanBeAllocatedAndFreed_9) {
  constexpr size_t kSize = 64;
  void* p = gmalloc(kSize);
  ASSERT_NE(p, nullptr);
  std::free(p);
}

// ---------- Boundary conditions ----------

TEST(GMallocTest_9, ZeroSizeReturnsNull_9) {
  EXPECT_EQ(gmalloc(0), nullptr);
}

TEST(GMallocTest_9, ZeroSizeIgnoresCheckOverflowAndReturnsNull_9) {
  EXPECT_EQ(gmalloc(0, /*checkoverflow=*/true), nullptr);
}

// ---------- Exceptional / error cases (observable) ----------
//
// We can only safely test the "returns nullptr" failure path when checkoverflow=true.
// The "abort" path would terminate the process; we test that via a death test, but
// only if we can reliably trigger it. To avoid flakiness, we gate that death test
// on detecting that a huge malloc actually fails in this environment.

TEST(GMallocTest_9, HugeAllocationWithCheckOverflowTrueReturnsNullWhenMallocFails_9) {
  const size_t huge = HugeSizeLikelyToFail();
  void* p = gmalloc(huge, /*checkoverflow=*/true);

  // If malloc unexpectedly succeeds (rare but possible in some environments with
  // overcommit), free and skip the strict failure assertion.
  if (p != nullptr) {
    std::free(p);
    GTEST_SKIP() << "malloc(" << huge << ") unexpectedly succeeded; cannot validate failure path.";
  }

  EXPECT_EQ(p, nullptr);
}

// Death tests require gtest to be built with death test support.
TEST(GMallocTest_9, HugeAllocationWithCheckOverflowFalseAbortsWhenMallocFails_9) {
  const size_t huge = HugeSizeLikelyToFail();

  // Probe malloc behavior first to reduce flakiness: if it succeeds, skip death test.
  void* probe = std::malloc(huge);
  if (probe != nullptr) {
    std::free(probe);
    GTEST_SKIP() << "malloc(" << huge << ") unexpectedly succeeded; cannot reliably trigger abort.";
  }

  // Now we expect gmalloc to abort (it may also print "Out of memory", but we don't assert on stderr).
  EXPECT_DEATH(
      {
        (void)gmalloc(huge, /*checkoverflow=*/false);
      },
      "");
}