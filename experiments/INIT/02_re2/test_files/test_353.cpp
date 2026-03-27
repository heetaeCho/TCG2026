// File: num_captures_walker_test.cc

#include <gtest/gtest.h>
#include <type_traits>

// The production code indicates these live under namespace re2.
#include "re2/regexp.h"

namespace {

using re2::NumCapturesWalker;
using re2::Ignored;

TEST(NumCapturesWalkerTest_353, DefaultConstructible_InitialCaptureZero_353) {
  // Normal operation: default-constructed object should report an initial count.
  NumCapturesWalker w;
  // Observable via public API only.
  EXPECT_EQ(w.ncapture(), 0);
}

TEST(NumCapturesWalkerTest_353, Ncature_IsIdempotent_353) {
  // Calling ncapture() should not mutate state (observable behavior).
  NumCapturesWalker w;
  const int first = w.ncapture();
  const int second = w.ncapture();
  EXPECT_EQ(first, second);
}

TEST(NumCapturesWalkerTest_353, TypeAlias_IgnoredIsInt_353) {
  // Interface/type check: Ignored should be an alias for int (per interface).
  EXPECT_TRUE((std::is_same<Ignored, int>::value));
}

TEST(NumCapturesWalkerTest_353, Traits_NotCopyableOrAssignable_353) {
  // Boundary/exception-like at the type level: verify copying is not allowed.
  EXPECT_FALSE((std::is_copy_constructible<NumCapturesWalker>::value));
  EXPECT_FALSE((std::is_copy_assignable<NumCapturesWalker>::value));
}

TEST(NumCapturesWalkerTest_353, ReturnType_NcaptureReturnsInt_353) {
  // Interface contract: ncapture() returns an int.
  EXPECT_TRUE(
      (std::is_same<decltype(std::declval<NumCapturesWalker&>().ncapture()), int>::value));
}

}  // namespace
