// File: named_captures_walker_shortvisit_test.cc

#include <climits>
#include "gtest/gtest.h"

// Include the headers that declare re2::NamedCapturesWalker and re2::Regexp.
// Adjust the include paths if your project layout differs.
#include "re2/regexp.h"

namespace re2 {

// Minimal wrapper so we can instantiate and call ShortVisit().
class TestableNamedCapturesWalker : public NamedCapturesWalker {
 public:
  using NamedCapturesWalker::ShortVisit;
};

class NamedCapturesWalkerTest_360 : public ::testing::Test {
 protected:
  TestableNamedCapturesWalker walker_;
};

// --- Normal operation: returns input value ---

TEST_F(NamedCapturesWalkerTest_360, ReturnsSameValue_Positive_360) {
  Ignored in = 42;
  // Passing nullptr for Regexp* is acceptable here since interface does not
  // specify usage of the pointer for return behavior; we assert only the return.
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

TEST_F(NamedCapturesWalkerTest_360, ReturnsSameValue_Zero_360) {
  Ignored in = 0;
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

TEST_F(NamedCapturesWalkerTest_360, ReturnsSameValue_Negative_360) {
  Ignored in = -7;
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

// --- Boundary conditions on the Ignored (int) value ---

TEST_F(NamedCapturesWalkerTest_360, ReturnsSameValue_IntMax_360) {
  Ignored in = INT_MAX;
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

TEST_F(NamedCapturesWalkerTest_360, ReturnsSameValue_IntMin_360) {
  Ignored in = INT_MIN;
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

// --- Exceptional / edge input: null Regexp* pointer ---

TEST_F(NamedCapturesWalkerTest_360, HandlesNullRegexpPointer_360) {
  Ignored in = 1234;
  // Verifies that providing a null Regexp* does not alter the observable return.
  Ignored out = walker_.ShortVisit(/*re=*/nullptr, in);
  EXPECT_EQ(out, in);
}

}  // namespace re2
