// File: ./TestProjects/re2/testing/repetition_walker_shortvisit_test_498.cc

#include <gtest/gtest.h>

namespace re2 {
// Forward declarations only — rely on the real implementation at link time.
class Regexp;
class RepetitionWalker {
public:
  int ShortVisit(Regexp* re, int parent_arg);
};
}  // namespace re2

// A simple fixture in case setup/teardown is needed later.
class RepetitionWalkerTest_498 : public ::testing::Test {
protected:
  re2::RepetitionWalker walker_;
};

// [Normal] ShortVisit returns 0 for a null Regexp pointer.
TEST_F(RepetitionWalkerTest_498, ShortVisitReturnsZeroWithNullRegexp_498) {
  int result = walker_.ShortVisit(/*re=*/nullptr, /*parent_arg=*/123);
  EXPECT_EQ(result, 0);
}

// [Boundary] ShortVisit ignores parent_arg values (negative, zero, positive)
// and still returns 0.
TEST_F(RepetitionWalkerTest_498, ShortVisitReturnIsZeroForAnyParentArg_498) {
  EXPECT_EQ(walker_.ShortVisit(nullptr, 0), 0);
  EXPECT_EQ(walker_.ShortVisit(nullptr, -1), 0);
  EXPECT_EQ(walker_.ShortVisit(nullptr, 1), 0);
  EXPECT_EQ(walker_.ShortVisit(nullptr, std::numeric_limits<int>::min()), 0);
  EXPECT_EQ(walker_.ShortVisit(nullptr, std::numeric_limits<int>::max()), 0);
}

// [Stability] Multiple calls should consistently return 0 (no observable state).
TEST_F(RepetitionWalkerTest_498, ShortVisitIsIdempotentAcrossCalls_498) {
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(walker_.ShortVisit(nullptr, i), 0) << "Call #" << i << " did not return 0";
  }
}
