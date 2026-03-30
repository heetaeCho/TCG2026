// File: prefilter_walker_test_559.cc

#include <gtest/gtest.h>
#include <type_traits>

// Pull in the implementation so the nested type is available.
// Adjust the include path if your build differs.
#include "re2/prefilter.cc"

using re2::Prefilter;

class PrefilterWalkerTest_559 : public ::testing::Test {};

// --- Normal operation: constructor parameter is reflected by latin1() ---

TEST_F(PrefilterWalkerTest_559, Latin1TrueReturnsTrue_559) {
  Prefilter::Walker w(/*latin1=*/true);
  EXPECT_TRUE(w.latin1());
}

TEST_F(PrefilterWalkerTest_559, Latin1FalseReturnsFalse_559) {
  Prefilter::Walker w(/*latin1=*/false);
  EXPECT_FALSE(w.latin1());
}

// --- Boundary-ish sanity: multiple calls are consistent (idempotent read) ---

TEST_F(PrefilterWalkerTest_559, Latin1ConsistentAcrossCalls_559) {
  Prefilter::Walker w(/*latin1=*/true);
  EXPECT_TRUE(w.latin1());
  EXPECT_TRUE(w.latin1());
  EXPECT_TRUE(w.latin1());
}

// --- Interface/traits checks (no implementation inference) ---

// The known interface indicates copy-operations are deleted.
// Verify via type traits at compile time.
TEST_F(PrefilterWalkerTest_559, WalkerIsNotCopyConstructible_559) {
  static_assert(!std::is_copy_constructible<Prefilter::Walker>::value,
                "Walker should not be copy constructible");
  SUCCEED();
}

TEST_F(PrefilterWalkerTest_559, WalkerIsNotCopyAssignable_559) {
  static_assert(!std::is_copy_assignable<Prefilter::Walker>::value,
                "Walker should not be copy assignable");
  SUCCEED();
}
