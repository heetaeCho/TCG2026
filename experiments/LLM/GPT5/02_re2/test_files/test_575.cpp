// File: prefilter_tree_print_unittest_575.cc

#include <gtest/gtest.h>
#include "re2/prefilter_tree.h"

namespace re2 {

// We treat PrefilterTree as a black box. The only observable effect of
// PrintPrefilter(int) in this constrained context is its behavior when called
// with invalid indices (boundary/error conditions). Since the method indexes
// into an internal vector, calling it with out-of-range indices is expected
// to result in process death (undefined access / assert), which we verify
// using death tests. We deliberately avoid constructing or relying on any
// Prefilter objects or internal state.

#if GTEST_HAS_DEATH_TEST

// Boundary/Error: Calling with 0 when no prefilters were added.
// Expect: process terminates (out-of-range access).
TEST(PrefilterTreeTest_575, PrintPrefilter_ZeroIndexWithoutSetup_575) {
  PrefilterTree tree;  // default-constructed; no setup performed
  ASSERT_DEATH(
      {
        // Intentionally exercising an observable boundary/error path.
        tree.PrintPrefilter(0);
      },
      ".*");
}

// Boundary/Error: Negative index.
// Expect: process terminates (invalid/underflow index).
TEST(PrefilterTreeTest_575, PrintPrefilter_NegativeIndex_575) {
  PrefilterTree tree;
  ASSERT_DEATH(
      {
        tree.PrintPrefilter(-1);
      },
      ".*");
}

// Boundary/Error: Very large positive index.
// Expect: process terminates (out-of-range access).
TEST(PrefilterTreeTest_575, PrintPrefilter_LargeOutOfRangeIndex_575) {
  PrefilterTree tree;
  const int kHuge = 1 << 20;  // sufficiently large to be out of range
  ASSERT_DEATH(
      {
        tree.PrintPrefilter(kHuge);
      },
      ".*");
}

#endif  // GTEST_HAS_DEATH_TEST

}  // namespace re2
